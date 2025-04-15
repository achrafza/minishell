#include "../minishell.h"

t_env	*push_env(t_env *head, char **new_env)
{
	t_env	*node;

	if (!new_env || !*new_env)
		return (head);
	node = create_env_node(*new_env);
	if (!node)
		return (head);
	node->next = head;
	return (node);
}

t_env	*create_env_node(char *env_str)
{
	t_env	*new_node;
	char	*ptr_to_tosawi;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	ptr_to_tosawi = ft_strchr(env_str, '=');
	if (!ptr_to_tosawi)
	{
		new_node->key = ft_strdup(env_str);
		new_node->value = NULL;
	}
	else
	{
		new_node->key = strndup(env_str, ptr_to_tosawi - env_str);
		new_node->value = strdup(ptr_to_tosawi + 1);
	}
	if (!new_node->key || (ptr_to_tosawi && !new_node->value))
	{
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

t_env	*env_list_from_array(char **env)
{
	t_env *head = NULL;
	t_env *next;
	int i = 0;

	while (env && env[i])
	{
		next = create_env_node(env[i]);
		if (!next)
			return (head);
		if (!head)
			head = next;
		else
		{
			t_env *tmp = head;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = next;
		}
		i++;
	}
	return (head);
}