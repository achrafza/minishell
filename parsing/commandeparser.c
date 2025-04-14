
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandeparser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 03:09:11 by azahid            #+#    #+#             */
/*   Updated: 2025/04/14 08:49:52 by azahid           ###   ########.fr       */
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

void	push_to_list(t_chars **head, char *str, int type)
{
	t_chars	*new_node;
	t_chars	*temp;

	new_node = malloc(sizeof(t_chars));
	if (!new_node)
		return ;
	new_node->str = str;
	new_node->type = type;
	if (!new_node->str)
	{
		free(new_node);
		return ;
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
}

/* gets the whole command and stores it inside t_comm struct ,
	its stored in the heap
the address is given to a variable inside the struct called "commande"*/

void	get_full_command(t_comm *com, char *prompt)
{
	char	*fullcom;

	if (!prompt || !*prompt)
	{
		com->commande = NULL;
		return ;
	}
	fullcom = ft_strdup(prompt);
	if (!fullcom)
	{
		com->commande = NULL;
		return ;
	}
	com->commande = fullcom;
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
  int i =0;

	if (!arr || !com)
		return -1;
	setter(com);
	loader(arr, com);
	com->env = env;
	com->p_com = p_com_split(arr);
  while(com->p_com && com->p_com[i])
  {    

    com->p_com[i] = parser(com->p_com[i], env);
    i++;
  }
  if (!com  || !com->p_com){
      perror("syntax error");
      return 1;
  }
	if (check_builtin(com))
  		com->p_com = createargs(com);
	com->commande = arr;
	if (DEBUG_MODE)
		print_t_comm(com);
	if (DBG_ENV)
		print_t_env(com);
	return (0);
}

/*a function that processes if a redirection is found ,
	pushes it into a linked list
that holds strings
PS : it also ignores if the redirections are quoted
*/
/*void	process_redirection(t_comm *com, char *token, int is_input)
{
	char	**parts;
	int		i;

	parts = ft_split(token, ' ');
	if (!parts)
		return ;
	i = 0;
	while (parts[i])
	{
		if (is_input && ft_strcmp(parts[i], "<") == 0)
		{
			if (!parts[i + 1])
			{
				fprintf(stderr, "Syntax error: no filename after '<'\n");
				break ;
			}
			push_to_list(&com->infile, parts[i + 1], -1);
			i++;
		}
		else if (!is_input && ft_strcmp(parts[i], ">") == 0)
		{
			if (!parts[i + 1])
			{
				fprintf(stderr, "Syntax error: no filename after '>'\n");
				break ;
			}
			push_to_list(&com->outfile, parts[i + 1], -1);
			i++;
		}
		i++;
	}
	// Free parts
	i = 0;
	while (parts[i])
	{
		free(parts[i]);
		i++;
	}
	free(parts);
}*/

/*fills the input arg in the comm struct ,
	only fills the ones with '<' aka input*/

/*void	fill_inputs(t_comm *com)
{
	if (!com || !com->p_com)
		return ;
	for (int i = 0; com->p_com[i]; i++)
	{
		if (ft_strchr(com->p_com[i], '<'))
		{
			process_redirection(com, com->p_com[i], 1);
		}
	}
}*/

/*same as above , for outputs*/

// void	fill_outputs(t_comm *com)
// {
// 	if (!com || !com->p_com)
// 		return ;
// 	for (int i = 0; com->p_com[i]; i++)
// 	{
// 		if (ft_strchr(com->p_com[i], '>'))
// 		{
// 			process_redirection(com, com->p_com[i], 0);
// 		}
// 	}
// }
