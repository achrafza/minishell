/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:54:21 by azahid            #+#    #+#             */
/*   Updated: 2025/04/07 23:54:22 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*function used for debugging purposes , prints the whole content
of the p_comm struct used to parse the initial command*/

void	print_t_comm(t_comm *cmd)
{
	t_chars	*current_infile;
	// t_env	*current_env;
	
	if (cmd == NULL)
		return ;
	printf("p_com:\n");
	if (cmd->p_com)
	{
		for (int i = 0; cmd->p_com[i] != NULL; i++)
			printf("[%s]\n", cmd->p_com[i]);
	}
	printf("commande: ['%s']\n", cmd->commande);
	printf("redirections:\n");
	current_infile = cmd->redirections;
	while (current_infile)
	{
		printf("[%s] (type: %s)\n", current_infile->str,
			current_infile->type ? "output (>)" : "input (<)");
		current_infile = current_infile->next;
	}
	// printf("env:\n");
	// current_env = cmd->env;
	// while (current_env)
	// {
	// 	printf("[%s]\n", current_env->env);
	// 	current_env = current_env->next;
	// }
}
