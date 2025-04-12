#include "../minishell.h"

char    *pwd(void)
{
    char buff[PATH_MAX];
    char *path;

    getcwd(buff, sizeof(buff));
    path = ft_strdup(buff);
    return (path);
}