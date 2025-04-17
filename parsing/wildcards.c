#include "../minishell.h"

static int match_pattern(const char *pattern, const char *str)
{
    if (!*pattern && !*str)
        return (1);
    if (*pattern == '*')
    {
        pattern++;
        if (!*pattern)
            return (1);
        while (*str)
        {
            if (match_pattern(pattern, str))
                return (1);
            str++;
        }
        return (match_pattern(pattern, str));
    }
    if (!*str)
        return (0);
    if (*pattern == '?' || *pattern == *str)
        return (match_pattern(pattern + 1, str + 1));
    return (0); // Characters don't match
}

t_chars *parse_wildcards(char *wildin, t_comm *com)
{
    DIR *dir;
    struct dirent *entry;
    t_chars *new_nodes = NULL;
    t_chars *last_node = NULL;

    if (!wildin || !com)
        return (NULL);

    if (!ft_strchr(wildin, '*') && !ft_strchr(wildin, '?'))
    {
        t_chars *node = malloc(sizeof(t_chars));
        if (!node)
            return (NULL);
        node->str = ft_strdup(wildin);
        node->type = 0;
        node->next = NULL;
        if (!node->str)
        {
            free(node);
            return (NULL);
        }
        return (node);
    }
    dir = opendir(".");
    if (!dir)
    {
        perror("opendir");
        t_chars *node = malloc(sizeof(t_chars));
        if (!node)
            return (NULL);
        node->str = ft_strdup(wildin);
        node->type = 0;
        node->next = NULL;
        if (!node->str)
        {
            free(node);
            return (NULL);
        }
        return (node);
    }

    // Read directory
    while ((entry = readdir(dir)) != NULL)
    {
        // Skip . and ..
        if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0)
            continue;

        // Check if file name matches the pattern
        if (match_pattern(wildin, entry->d_name))
        {
            t_chars *node = malloc(sizeof(t_chars));
            if (!node)
            {
                free_chars(new_nodes);
                closedir(dir);
                return (NULL);
            }
            node->str = ft_strdup(entry->d_name);
            node->type = 0; // File name type
            node->next = NULL;

            if (!node->str)
            {
                free(node);
                free_chars(new_nodes);
                closedir(dir);
                return (NULL);
            }

            if (!new_nodes)
            {
                new_nodes = node;
                last_node = node;
            }
            else
            {
                last_node->next = node;
                last_node = node;
            }
        }
    }

    if (!new_nodes)
    {
        t_chars *node = malloc(sizeof(t_chars));
        if (!node)
        {
            closedir(dir);
            return (NULL);
        }
        node->str = ft_strdup(wildin);
        node->type = 0;
        node->next = NULL;
        if (!node->str)
        {
            free(node);
            closedir(dir);
            return (NULL);
        }
        new_nodes = node;
    }

    closedir(dir);
    return (new_nodes);
}