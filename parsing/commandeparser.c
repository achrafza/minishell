
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandeparser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 03:09:11 by azahid            #+#    #+#             */
/*   Updated: 2025/04/15 04:33:18 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
}
/*splits the commands into multiple chunks using the pipes*/

int	commandeparser(char *arr, t_comm *com, t_env *env)
{
	int i;
	int status;
	char *tmp;

	i = 0;
	if (!arr || !com)
		return (-1);
	setter(com);
	status = loader(arr, com, env);
	com->env = env;
	com->p_com = p_com_split(arr);
	if (!com->p_com)
	{
		perror("syntax error");
		return (1);
	}
	while (com->p_com && com->p_com[i])
	{
		tmp = parser(com->p_com[i], env);
		if (!tmp)
		{
			free2d(com->p_com);
			com->p_com = NULL;
			return (1);
		}
		free(com->p_com[i]);
		com->p_com[i] = tmp;
		i++;
	}
	if (!com || !com->p_com)
	{
		perror("syntax error");
		return (1);
	}
	if (check_builtin(com))
	{
		com->p_com = createargs(com);
		if (!com->p_com)
		{
			free(com->commande);
			return (1);
		}
	}

	com->commande = malloc(sizeof(t_args));
	if (!com->commande)
		return (1);
	com->commande->str = ft_split(arr, ' ');
	if (!com->commande->str)
	{
		free(com->commande);
		com->commande = NULL;
		return (1);
	}
	com->commande->next = NULL;

	if (DEBUG_MODE)
		print_t_comm(com);
	if (DBG_ENV)
		print_t_env(com);
	return (0);
}