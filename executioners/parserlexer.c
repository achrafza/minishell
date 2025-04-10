/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserlexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:50:34 by azahid            #+#    #+#             */
/*   Updated: 2025/04/07 17:53:38 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*still unfinished for now , but sets the whole struct to 0 for future calls ,
	then fills
the struct based on their existence . for now the whole 4 args in the struct are filled*/

int parserlexer(char *input, t_comm **coms, char ***str)
{
	*str = ft_split(input, '|');
	if (!*str)
		return (-1);
	if (!**str) 
	{
		free2d(*str);
		*str = NULL;
		return (-1);
	}
	*coms = arrayallocator(*str);
	if (!*coms) 
	{
		free2d(*str);
		*str = NULL;
		return (-1);
	}
	return (0);
}