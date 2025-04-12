/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 01:45:49 by azahid            #+#    #+#             */
/*   Updated: 2025/04/12 03:13:40 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
  if (com->p_com)
  {
    if (!ft_strcmp(com->p_com[0], "pwd"))
      return (printf("%s\n",pwd()), 0);
    else if (!ft_strcmp(com->p_com[0], "exit"))
      exit_prog();
    else if (!ft_strcmp(com->p_com[0], "unset"))
      return (unset(&com->env, com->p_com[1]), 0);
    else if(!ft_strcmp(com->p_com[0], "cd"))
      return (cd (get_next_word(com->commande), com->env), 0);
    /*else if(!ft_strcmp(com->p_com[0], "debug"))
      return (debug = 1 , 0);*/
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
  }
  return (1);
}

char **envtodoublearr(t_env *e)
{
	int count = 0;
	t_env *tmp = e;

	while (tmp)
	{
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
		envp[i] = tmp->env;
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return envp;
}

int execute(t_comm *com,char **envp)
{
  if (!check_builtin(com))
  {
    exec_builtin(com);
    return (0);
  }
  if (!com->p_com)
  {
    perror("commande not found");
    return 1;
  }
  int id = fork();
  if (id != 0)
    return (1);
  if (com->p_com)
  {
    execve(com->p_com[0], com->p_com, envp);
    perror("commande not found");
    return (1);
  }
  return (id);
}
