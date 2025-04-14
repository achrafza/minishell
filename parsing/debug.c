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

void	print_t_comm(t_comm *cmd)
{
	t_chars	*current_infile;

	if (cmd == NULL)
		return ;
	printf("\033[0;34m----------------- Command Info -----------------\033[0m\n");
	printf("\033[0;32m p_com:\033[0m\n");
	if (cmd->p_com)
	{
		for (int i = 0; cmd->p_com[i] != NULL; i++)
			printf("\033[0;33m [%s]\033[0m\n", cmd->p_com[i]);
	}
	printf("\033[0;32m commande: \033[0m['%s']\n", cmd->commande);
	printf("\033[0;32m redirections:\033[0m\n");
	current_infile = cmd->redirections;
	while (current_infile)
	{
		printf("\033[0;36m [%s] \033[0m(type: \033[0;35m%s\033[0m)\n",
			current_infile->str, current_infile->type ? "output (>)" : "input (<)");
		current_infile = current_infile->next;
	}
}

void	print_t_env(t_comm *cmd)
{
	char	input;
	char	choice;
	t_env	*current_env;

	printf("\033[0;32m Do you want to print the env? (y/n): \033[0m");
	scanf(" %c", &input);
	if (input == 'y' || input == 'Y')
	{
		printf("\033[0;32m What would you like to print?\n");
		printf("1. Keys only\n2. Values only\n3. Both keys and values\n\033[0m");
		scanf(" %c", &choice);

		current_env = cmd->env;
		while (current_env)
		{
			if (choice == '1' && current_env->key)
				printf("\033[0;33m %s\033[0m\n", current_env->key);
			else if (choice == '2' && current_env->value)
				printf("\033[0;33m %s\033[0m\n", current_env->value);
			else if (choice == '3' && current_env->key && current_env->value)
				printf("\033[0;33m [%s=%s]\033[0m\n", current_env->key, current_env->value);
			current_env = current_env->next;
		}
	}
}