/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:43:43 by azahid            #+#    #+#             */
/*   Updated: 2025/03/27 20:43:46 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

int		g_signal;

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char *envp[])
{
	char	*input;

	(void)ac;
	(void)av;
	(void)envp;
	setup_signals();
	read_history("history.txt");
	while ((input = readline("minishell >> ")) != NULL)
	{
		if (*input)
			add_history(input);
		parserlexer(input, envp);
		free(input);
	}
	write(1, "exit\n", 5); // Handle Ctrl+D exiting
	rl_clear_history();
	return (0);
}
