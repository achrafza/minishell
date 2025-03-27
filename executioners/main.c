
#include "../minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int	g_signal;

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
		parserlexer(input);
		free(input);
	}

	write(1, "exit\n", 5); // Handle Ctrl+D exiting
	rl_clear_history();
	return (0);
}
