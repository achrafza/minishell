#include "../minishell.h"

int cd(char *path)
{
    if (!path)
        return (-1);
    if (chdir(path))
        return (perror("Error in cd"), -1);
    return (0);
}