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

int execute(t_comm *com,char **envp){
  if (!com->p_com){
    perror("commande not found");
    return 1;}
  int id = fork();
  if (id != 0)
    return (1);
  if (com->p_com){
    execve(com->p_com[0], com->p_com, envp);
    perror("commande not found");
    return (1);
  }
  return (id);
}
