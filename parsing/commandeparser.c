
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandeparser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 03:09:11 by azahid            #+#    #+#             */
/*   Updated: 2025/04/17 08:36:06 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

/* this checks for spaces in a character , pretty basic*/
int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

/* this pushes a string into a linked list , pretty basic hh*/

int	push_to_list(t_chars **head, char *str, int type)
{
	t_chars	*new_node;
	t_chars	*temp;

	new_node = malloc(sizeof(t_chars));
	if (!new_node)
		return (1);
	new_node->str = str;
	new_node->type = type;
	if (!new_node->str)
	{
		free(new_node);
		return (1);
	}
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
	return (0);
}

/* gets the whole command and stores it inside t_comm struct ,
	its stored in the heap
the address is given to a variable inside the struct called "commande"*/

void	get_full_command(t_comm *com, char *prompt)
{
	t_args	*new;

	if (!prompt || !*prompt)
	{
		com->commande = NULL;
		return ;
	}
	new = malloc(sizeof(t_args));
	if (!new)
	{
		com->commande = NULL;
		return ;
	}
	new->str = ft_split(prompt, ' ');
	new->next = NULL;
	com->commande = new;
}
// sets all values to zero for no problem in pushing elements

void	setter(t_comm *com)
{
	com->commande = NULL;
	com->p_com = NULL;
	com->heardoc = NULL;
	com->redirections = NULL;
	com->env = NULL;
  com->infile = -1;
  com->outfile = -1;
}
/*splits the commands into multiple chunks using the pipes*/



int commandeparser(char *arr, t_comm *com, t_env *env)
{
    int status;
    char **tmp;
    t_chars *curr, *prev, *nxt;

    if (!arr || !com)
        return (-1);
    setter(com);
    status = loader(arr, com, env);
    com->env = env;
    com->p_com = p_com_split(arr);
    if (!com->p_com || !com->p_com->str)
    {
        perror("syntax error");
        free_chars(com->p_com);
        com->p_com = NULL;
        return (1);
    }
    curr = com->p_com;
    prev = NULL;

    while (curr)
    {
        if (!curr->str) // Fix: Check for NULL curr->str
        {
            free_chars(com->p_com);
            com->p_com = NULL;
            return (1);
        }
        if (curr->str[0] == '\"')
            tmp = parser(curr->str, env, 0, 0);
        else
            tmp = parser(curr->str, env, 1, 0);
        if (!tmp)
        {
            free_chars(com->p_com);
            com->p_com = NULL;
            return (1);
        }
        nxt = curr->next; 
        free(curr->str);
        curr->str = NULL;

        t_chars *new_head = NULL;
        t_chars *new_tail = NULL;

        for (int j = 0; tmp[j]; j++)
        {
            t_chars *new_node = malloc(sizeof(t_chars));
            if (!new_node)
            {
                free2d(tmp);
                free_chars(com->p_com);
                com->p_com = NULL;
                return (1);
            }
            new_node->str = ft_strdup(tmp[j]);
            new_node->type = curr->type;
            new_node->next = NULL;

            if (!new_node->str)
            {
                free(new_node);
                free2d(tmp);
                free_chars(com->p_com);
                com->p_com = NULL;
                return (1);
            }

            if (!new_head)
            {
                new_head = new_node;
                new_tail = new_node;
            }
            else
            {
                new_tail->next = new_node;
                new_tail = new_node;
            }
        }
        if (!prev)
            com->p_com = new_head;
        else
            prev->next = new_head;
        if (new_tail)
            new_tail->next = nxt;
        else if (prev) 
            prev->next = nxt;
        free(curr); 
        curr = nxt;
        prev = new_tail ? new_tail : prev; 
        free2d(tmp);
    }

    if (!com || !com->p_com)
    {
        perror("syntax error");
        free_chars(com->p_com); 
        com->p_com = NULL;
        return (1);
    }
    if (check_builtin(com))
    {
        char *new_str = createargs(com);
        if (!new_str)
        {
            free_chars(com->p_com);
            com->p_com = NULL;
            free(com->commande); 
            com->commande = NULL;
            return (1);
        }
        com->p_com->str = new_str;
    }
    com->commande = malloc(sizeof(t_args));
    if (!com->commande)
    {
        free_chars(com->p_com);
        com->p_com = NULL;
        return (1);
    }
    com->commande->str = ft_split(arr, ' ');
    if (!com->commande->str)
    {
        free(com->commande);
        com->commande = NULL;
        free_chars(com->p_com);
        com->p_com = NULL;
        return (1);
    }
    com->commande->next = NULL;
    return (0);
}