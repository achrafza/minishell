/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserlexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvrk <dvrk@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:50:34 by azahid            #+#    #+#             */
/*   Updated: 2025/04/15 04:39:54 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

/*still unfinished for now , but sets the whole struct to 0 for future calls ,
	then fills
the struct based on their existence . for now the whole 4 args in the struct are filled*/

int	parserlexer(char *input, char **envp, t_env *env)
{
	int		size;
	char	**str;
	t_comm	*coms;

	size = 0;
	str = pipe_split(input);
	if (!str)
		return (-1);
	coms = arrayallocator(str, env);
	if (!coms)
		return (-1);
	size = double_array_size(str);
	if (coms && coms->env)
		envp = envtodoublearr(coms->env);
	if (size > 0)
		execute_all(coms,envp,size);
	//free_all_commande(coms, size);
	
	free2d(str);
	return 0;
}
