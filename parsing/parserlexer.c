/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserlexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:50:34 by azahid            #+#    #+#             */
/*   Updated: 2025/04/12 03:15:18 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*still unfinished for now , but sets the whole struct to 0 for future calls ,
	then fills
the struct based on their existence . for now the whole 4 args in the struct are filled*/

void	parserlexer(char *input, char **envp)
{
	int		size;
	char	**str;
	t_comm	*coms;
	t_env *env;
  int i = 0;
  int id = 0;

	env = env_list_from_array(envp);
	size = 0;
	str = ft_split(input, '|');
	coms = arrayallocator(str, env);
	size = double_array_size(str);
  while(i < size)
  {
    id = execute(&coms[i], envp);
    wait(NULL);
    i++;
  }

	free_all_commande(coms, size);
	// free_commande(coms);
	free2d(str);
	return ;
}
