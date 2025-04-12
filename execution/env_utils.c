#include "../minishell.h"

t_env *push_env(t_env *head, char **new_env)
{
	t_env *node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (head);
	node->env = *new_env;
	node->next = head;
	return (node);
}

t_env	*create_env_node(char *env_str)
{
	t_env *new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->env = strdup(env_str);
	if (!new_node->env)
	{
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