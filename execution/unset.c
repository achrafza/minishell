#include "../minishell.h"

int unset(t_env **env, char *var)
{
	t_env *curr = *env;
	t_env *prev = NULL;
	size_t len = ft_strlen(var);

	while (curr)
	{
		if (ft_strncmp(curr->env, var, len) == 0 && curr->env[len] == '=') {
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->env);
			free(curr);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (1);
}