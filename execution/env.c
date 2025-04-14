#include "../minishell.h"

void	env(t_comm *cmd)
{
	t_env *env;

	if (!cmd || !cmd->p_com || !cmd->p_com[0])
		return ;
	if (cmd->p_com[1])
	{
		printf("env: too many arguments\n");
		return ;
	}
	env = cmd->env;
	while (env)
	{
		if (env->env && *env->env)
			printf("%s\n", env->env);
		env = env->next;
	}
}