#include "../minishell.h"

int env(t_env *env)
{
	while (env)
	{
		printf("%s\n", env->env);
		env = env->next;
	}
	return (0);
}