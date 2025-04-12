#include "../minishell.h"

int env(t_env *env)
{
	while (env)
	{
		write(1, env->env, strlen(env->env));
		write(1, "\n", 1);
		env = env->next;
	}
	return (0);
}