/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 05:02:18 by azahid            #+#    #+#             */
/*   Updated: 2025/04/12 23:02:51 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/wait.h>
#include <unistd.h>

void  exit_prog(void)
{
  exit(0);
}

char *get_next_word(const char *str) 
{
  int i = 0;
  if (!str)
    return NULL;
  while (str[i] && isspace(str[i])) i++; 
  if (!str[i])
    return NULL;
  while (str[i] && !isspace(str[i])) i++; 
  while (str[i] && isspace(str[i])) i++; 

  int start = i;
  while (str[i] && !isspace(str[i])) i++; 
  if (start == i) return NULL;

  char *word = ft_strdup(str + start);

  
  while (str[i] && isspace(str[i])) i++;
  if (str[i] && !isspace(str[i])) 
  {
      free(word);
      return NULL; 
  }
  return word;
}

int  exec_builtin(t_comm *com)
{
	char *path = NULL;
	if (com->p_com)
	{
		if (!ft_strcmp(com->p_com[0], "pwd"))
		{
			path = pwd();
			if (!path)
				return (1);
			return (printf("%s\n", path), free(path), 0);
		}
		else if (!ft_strcmp(com->p_com[0], "exit"))
		exit_prog();
		else if (!ft_strcmp(com->p_com[0], "unset"))
		return (unset(&com->env, com->p_com[1]), 0);
		else if(!ft_strcmp(com->p_com[0], "cd"))
		return (cd (get_next_word(com->commande), com->env), 0);
		else if(!ft_strcmp(com->p_com[0], "echo"))
		return (echo(com->p_com), 0);
		else if(!ft_strcmp(com->p_com[0], "env"))
		return (env(com), 0);
		else if(!ft_strcmp(com->p_com[0], "export"))
		return (printf("export not here yet ;>\n"), 0);
  	}
  return (1);
}

int check_builtin(t_comm *com)
{
  if (com->p_com)
  {
    if (!ft_strcmp(com->p_com[0], "pwd"))
      return (0);
    else if (!ft_strcmp(com->p_com[0], "exit"))
		exit_prog();
    else if (!ft_strcmp(com->p_com[0], "unset"))
      return (unset(&com->env, com->p_com[1]), 0);
    else if(!ft_strcmp(com->p_com[0], "cd"))
      return (0);
	else if(!ft_strcmp(com->p_com[0], "echo"))
	  return (0);
	else if(!ft_strcmp(com->p_com[0], "env"))
	  return (0);
	else if(!ft_strcmp(com->p_com[0], "export"))
	  return (0);
  }
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
		return NULL;

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
				return NULL;
			}
			envp[i] = ft_strjoin(first_part, tmp->value);
			free(first_part);
			if (!envp[i])
			{
				free2d(envp);
				return NULL;
			}
			i++;
		}
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return envp;
}
int execute_all(t_comm *coms, char **envp, int size)
{
    if (size == 1 && coms[0].p_com && !check_builtin(&coms[0]))
    {
        char *cmd = coms[0].p_com[0];
        if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "exit") == 0 || 
            ft_strcmp(cmd, "export") == 0 || ft_strcmp(cmd, "unset") == 0)
        {
            return exec_builtin(&coms[0]);
        }
    }

    int pipes[2 * (size - 1)];
    int pids[size];
    int i = 0;

    while (i < size - 1)
    {
        if (pipe(pipes + i * 2) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
        i++;
    }

    i = 0;
    while (i < size)
    {
        pids[i] = fork();
        if (pids[i] == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pids[i] == 0)
        {
            if (i > 0)
                dup2(pipes[(i - 1) * 2], 0);
            if (i < size - 1)
                dup2(pipes[i * 2 + 1], 1);

            for (int j = 0; j < 2 * (size - 1); j++)
                close(pipes[j]);

            if (!coms[i].p_com || !coms[i].p_com[0])
            {
                perror("command not found");
                exit(127);
            }

            if (!check_builtin(&coms[i]))
            {
                exec_builtin(&coms[i]);
                exit(0);
            }
            else 
            {
                execve(coms[i].p_com[0], coms[i].p_com, envp);
                perror(coms[i].p_com[0]);
                exit(127);
            }
        }
        i++;
    }

    for (int i = 0; i < 2 * (size - 1); i++)
        close(pipes[i]);

    for (int i = 0; i < size; i++)
        waitpid(pids[i], NULL, 0);
    if (envp && *envp)
      free2d(envp);
    envp = NULL;

    return 0;
}