#include "../minishell.h"

void	export(char *arg, t_env *env)
{
	char *key, *value, *tosawi, *append_pos;
	t_env *tmp;
	int is_append = 0;

	// Check if env is initialized
	if (!env)
	{
		printf("minishell: export: environment not initialized\n");
		return ;
	}

	if (!arg || !*arg)
	{
		tmp = env;
		while (tmp)
		{
			if (tmp->key)
			{
				if (tmp->value)
					printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
				else
					printf("declare -x %s\n", tmp->key);
			}
			tmp = tmp->next;
		}
		env->exit_status = 0;
		return ;
	}

	append_pos = ft_strnstr(arg, "+=", ft_strlen(arg));
	tosawi = ft_strchr(arg, '=');
	if (append_pos)
	{
		is_append = 1;
		key = ft_substr(arg, 0, append_pos - arg);
		value = ft_strdup(append_pos + 2);
	}
	else if (tosawi)
	{
		key = ft_substr(arg, 0, tosawi - arg);
		value = ft_strdup(tosawi + 1);
	}
	else
	{
		key = ft_strdup(arg);
		value = NULL;
	}

	if (!key || !*key || !isalpha(key[0]) || ft_strchr(key, ' '))
	{
		printf("minishell: export: `%s': not a valid identifier\n", arg);
		if (key)
			free(key);
		if (value)
			free(value);
		env->exit_status = 1;
		return ;
	}

	// Check if key exists
	tmp = env;
	while (tmp)
	{
		if (tmp->key && ft_strcmp(tmp->key, key) == 0)
		{
			if (is_append && value && tmp->value)
			{
				char *new_value = ft_strjoin(tmp->value, value);
				free(tmp->value);
				free(value);
				tmp->value = new_value;
			}
			else if (value)
			{
				free(tmp->value);
				tmp->value = value;
			}
			else if (tosawi || append_pos)
			{
				// Empty value after = or +=
				free(tmp->value);
				tmp->value = ft_strdup("");
			}
			free(key);
			env->exit_status = 0;
			return ;
		}
		tmp = tmp->next;
	}

	// Key doesn't exist, create new node
	t_env *new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		printf("minishell: export: cannot allocate memory\n");
		free(key);
		if (value)
			free(value);
		env->exit_status = 1;
		return ;
	}

	new_node->key = key;
	new_node->value = value ? value : ((tosawi
				|| append_pos) ? ft_strdup("") : NULL);
	new_node->next = NULL;

	// Add to the end of the list
	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;

	env->exit_status = 0;
}