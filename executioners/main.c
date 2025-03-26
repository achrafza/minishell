
#include "../minishell.h"

int		g_signlal;
#define SIGMINE 30

void	closer(int signals)
{
	rl_clear_history();
	printf("exited");
	exit(1);
}
int	main(int ac, char **av, char *envp[])
{
	char	*input;

	signal(SIGTERM, closer);
	signal(SIGMINE, closer);
	read_history("history.txt"); // Load previous history
	while ((input = readline("minishell >> ")) != NULL)
	{
		if (*input)
			add_history(input);
		parserlexer(input);
		executer();
		free(input);
	}
	rl_clear_history();
	return (0);
}
