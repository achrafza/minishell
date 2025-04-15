/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:43:43 by azahid            #+#    #+#             */
/*   Updated: 2025/04/15 00:31:43 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

int		g_signal;

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	signal(SIGTERM, SIG_IGN);
}

int	main(int ac, char **av, char *envp[])
{
	char	*input;
	t_env 	*env;

	(void)ac;
	(void)av;
	(void)envp;
	env = env_list_from_array(envp);
	increment_shlvl(env);
	setup_signals();
	read_history("history.txt");
	while (1337)
	{
		input = readline("\x1b[1;35mminihell:~ \x1b[0m");
    	if (input == NULL) break;
			if (*input)
				add_history(input);
			parserlexer(input, envp, env);
			free(input);
	}
	write(1, "exit\n", 5);
	rl_clear_history();
	return (0);
}
