/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvrk <dvrk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 05:02:18 by azahid            #+#    #+#             */
/*   Updated: 2025/04/19 11:21:06 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

void exit_prog(t_comm *com)
{
    int status = 0;
    t_env *env = com ? com->env : NULL;

    if (env)
        status = env->exit_status;

    if (com && com->p_com && com->p_com->next)
    {
        char *arg = com->p_com->next->str;
        int i = 0;
        if (arg[0] == '-')
            i++;
        while (arg[i])
        {
            if (!isdigit(arg[i]))
            {
                printf("minishell: exit: %s: numeric argument required\n", arg);
                status = 2;
                break;
            }
            i++;
        }
        if (!status)
            status = atoi(arg);
    }

    if (env)
        env->exit_status = status;
    exit(status);
}

char *get_next_word(const char *str)
{
    int i = 0;
    int start;
    char *word;
    t_env *env = NULL;

    if (!str)
        return (NULL);
    while (str[i] && ft_isspace(str[i]))
        i++;
    if (!str[i])
        return (NULL);
    while (str[i] && !ft_isspace(str[i]))
        i++;
    while (str[i] && ft_isspace(str[i]))
        i++;
    start = i;
    while (str[i] && !ft_isspace(str[i]))
        i++;
    if (start == i)
        return (NULL);
    word = ft_strdup(str + start);
    if (!word)
    {
        printf("minishell: cannot allocate memory\n");
        if (env)
            env->exit_status = 1;
        return (NULL);
    }
    while (str[i] && ft_isspace(str[i]))
        i++;
    if (str[i] && !ft_isspace(str[i]))
    {
        free(word);
        printf("minishell: syntax error near unexpected token `%c'\n", str[i]);
        if (env)
            env->exit_status = 2;
        return (NULL);
    }
    return (word);
}

int exec_builtin(t_comm *com)
{
    char *path;

    if (!com || !com->p_com || !com->p_com->str || !com->env)
    {
        if (com && com->env)
            com->env->exit_status = 1;
        return (1);
    }
    if (!ft_strcmp(com->p_com->str, "pwd"))
    {
        path = pwd();
        if (!path)
        {
            printf("minishell: pwd: cannot get current directory\n");
            com->env->exit_status = 1;
            return (1);
        }
        printf("%s\n", path);
        free(path);
        com->env->exit_status = 0;
        return (0);
    }
    else if (!ft_strcmp(com->p_com->str, "exit"))
    {
        exit_prog(com);
        return (0);
    }
    else if (!ft_strcmp(com->p_com->str, "unset"))
    {
        if (!com->p_com->next || !com->p_com->next->str)
        {
            printf("minishell: unset: not enough arguments\n");
            com->env->exit_status = 1;
            return (1);
        }
        int ret = unset(&com->env, com->p_com->next->str);
        com->env->exit_status = ret;
        return (ret);
    }
    else if (!ft_strcmp(com->p_com->str, "cd"))
    {
        char *path = com->commande && com->commande->str ? com->commande->str[1] : NULL;
        int ret = cd(path, com->env);
        if (ret)
            printf("minishell: cd: %s: No such file or directory\n", path ? path : "");
        com->env->exit_status = ret;
        return (ret);
    }
    else if (!ft_strcmp(com->p_com->str, "echo"))
    {
        int ret = echo(com);
        com->env->exit_status = ret;
        return (ret);
    }
    else if (!ft_strcmp(com->p_com->str, "env"))
    {
        env(com);
        com->env->exit_status = 0;
        return (0);
    }
    else if (!ft_strcmp(com->p_com->str, "export"))
    {
        if (com->p_com->next)
            export(com->p_com->next->str, com->env);
        else
            export(NULL, com->env);
        return (1);
    }
    com->env->exit_status = 1;
    return (1);
}

int check_builtin(t_comm *com)
{
    if (!com || !com->p_com || !com->p_com->str)
        return (1);
    if (!ft_strcmp(com->p_com->str, "pwd"))
        return (0);
    else if (!ft_strcmp(com->p_com->str, "exit"))
        return (0);
    else if (!ft_strcmp(com->p_com->str, "unset"))
        return (0);
    else if (!ft_strcmp(com->p_com->str, "cd"))
        return (0);
    else if (!ft_strcmp(com->p_com->str, "echo"))
        return (0);
    else if (!ft_strcmp(com->p_com->str, "env"))
        return (0);
    else if (!ft_strcmp(com->p_com->str, "export"))
        return (0);
    return (1);
}

char **envtodoublearr(t_env *e)
{
    int count = 0;
    t_env *tmp = e;
    while (tmp)
    {
        if (tmp->key && tmp->value)
            count++;
        tmp = tmp->next;
    }
    char **envp = malloc(sizeof(char *) * (count + 1));
    if (!envp)
    {
        printf("minishell: cannot allocate memory\n");
        if (e)
            e->exit_status = 1;
        return (NULL);
    }
    tmp = e;
    int i = 0;
    while (tmp)
    {
        if (tmp->key && tmp->value)
        {
            char *first_part = ft_strjoin(tmp->key, "=");
            if (!first_part)
            {
                free2d(envp);
                printf("minishell: cannot allocate memory\n");
                tmp->exit_status = 1;
                return (NULL);
            }
            envp[i] = ft_strjoin(first_part, tmp->value);
            free(first_part);
            if (!envp[i])
            {
                free2d(envp);
                printf("minishell: cannot allocate memory\n");
                tmp->exit_status = 1;
                return (NULL);
            }
            i++;
        }
        tmp = tmp->next;
    }
    envp[i] = NULL;
    return (envp);
}

char	**list_to_array(t_chars *list)
{
	int		size;
	int		i;
	char	**array;

	size = 0;
	t_chars *tmp = list;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	i = 0;
  t_chars *tt = list;
	while (tt)
	{
		array[i] = ft_strdup(tt->str); // don't strdup to avoid leaks (share same ptr)
		i++;
		tt = tt->next;
	}
	array[i] = NULL;
	return (array);
}
int execute_all(t_comm *coms, char **envp, int size)
{
    if (!coms || size <= 0)
    {
        if (coms && coms[0].env)
            coms[0].env->exit_status = 1;
        free2d(envp);
        return (1);
    }
    if (size == 1 && coms[0].p_com && !check_builtin(&coms[0]))
    {
        int ret = exec_builtin(&coms[0]);
        free2d(envp);
        return (coms[0].env ? coms[0].env->exit_status : ret);
    }

    int pipes[2 * (size - 1)];
    int pids[size];
    int i = 0;

    while (i < size - 1)
    {
        if (pipe(pipes + i * 2) == -1)
        {
            printf("minishell: pipe: Resource temporarily unavailable\n");
            for (int j = 0; j < i * 2; j++)
                close(pipes[j]);
            if (coms && coms[0].env)
                coms[0].env->exit_status = 1;
            free2d(envp);
            return (1);
        }
        i++;
    }

    i = 0;
    while (i < size)
    { 
        pids[i] = fork();
        if (pids[i] == -1)
        {
            perror("minishell:");
            for (int j = 0; j < 2 * (size - 1); j++)
                close(pipes[j]);
            if (coms && coms[0].env)
                coms[0].env->exit_status = 1;
            free2d(envp);
            return (1);
        }
        if (pids[i] == 0)
        {
            int in = 0,out = 0;
            if(handle_redirections(coms,i,&in,&out) != 0)
            {
              free2d(envp);
              perror("failed in redirection");
              exit(1);
            }
            if (i > 0 && !in)
                dup2(pipes[(i - 1) * 2], 0);
            if (i < size - 1 && !out)
                dup2(pipes[i * 2 + 1], 1);
            for (int j = 0; j < 2 * (size - 1); j++)
                close(pipes[j]);
            char **exec =  list_to_array(coms[i].p_com);
            if (!exec || !exec[0])
            {
                perror("minishell:");
                if (coms[i].env)
                    coms[i].env->exit_status = 127;
                free2d(envp);
                exit(127);
            }
            if (!check_builtin(&coms[i]))
            {
                int ret = exec_builtin(&coms[i]);
                free2d(envp);
                exit(ret);
            }
            else
            {
                execve(exec[0], exec, envp);
                perror("minishell: %s: command not found");
                if (coms[i].env)
                    coms[i].env->exit_status = 127;
                free2d(envp);
                exit(127);
            }
        }
        i++;
    }

    for (int i = 0; i < 2 * (size - 1); i++)
        close(pipes[i]);

    int status = 0;
    for (int i = 0; i < size; i++)
    {
        waitpid(pids[i], &status, 0);
        if (WIFEXITED(status))
            status = WEXITSTATUS(status);
        else
            status = 1;
        if (coms && coms[0].env)
            coms[0].env->exit_status = status;
    }
    free2d(envp);
    return (coms && coms[0].env ? coms[0].env->exit_status : status);
}
