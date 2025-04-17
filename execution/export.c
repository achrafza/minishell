#include "../minishell.h"

void export(char *arg, t_env *env)
{
    char *key, *value, *tosawi;
    t_env *tmp;

    //is env there anywaysss?
    if (!env)
    {
        printf("minishell: export: environment not initialized\n");
        return;
    }
    
    //print alll args with declare -x before , not sure if i should keep it that way
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
        return;
    }

    // Case 2: Argument provided, parse KEY=value
    tosawi = ft_strchr(arg, '=');
    if (!tosawi)
    {
        key = ft_strdup(arg);
        value = NULL;
    }
    else
    {
        key = ft_substr(arg, 0, tosawi - arg);
        value = ft_strdup(tosawi + 1);
    }

    //key parse
    if (!key || !*key || !isalpha(key[0]) || ft_strchr(key, ' '))
    {
        printf("minishell: export: `%s': not a valid identifier\n", arg);
        if (key)
            free(key);
        if (value)
            free(value);
        env->exit_status = 1;
        return;
    }

    //if it exists
    tmp = env;
    while (tmp)
    {
        if (tmp->key && ft_strcmp(tmp->key, key) == 0)
        {
            if (value)
            {
                free(tmp->value);
                tmp->value = value;
            }
            else if (tosawi)
            {
                //if nothing after the key we leave it empty ig
                free(tmp->value);
                tmp->value = ft_strdup("");
            }
            free(key);
            env->exit_status = 0;
            return;
        }
        tmp = tmp->next;
    }

    //if the key doesnt exist we makeee a neew one
    t_env *new_node = malloc(sizeof(t_env));
    if (!new_node)
    {
        printf("minishell: export: cannot allocate memory\n");
        free(key);
        if (value)
            free(value);
        env->exit_status = 1;
        return;
    }

    new_node->key = key;
    new_node->value = value ? value : (tosawi ? ft_strdup("") : NULL);
    new_node->next = NULL;

    //adds stuff to the end.
    tmp = env;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;

    env->exit_status = 0;
}