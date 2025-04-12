#include "../minishell.h"

int cd(char *path, t_env *e)
{
    if (!path)
    {
        while (e->env)
        {
            printf("%s\n", e->env + 5);
            if (!ft_strncmp(e->env , "HOME=", 5))
            {
                chdir(ft_strdup(e->env + 5)); 
                break;
            }
            e = e->next;
        }
    }
    else if (chdir(path))
        return (perror("Error in cd"), -1);
    return (0);
}