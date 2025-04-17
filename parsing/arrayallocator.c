/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrayallocator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 01:26:38 by azahid            #+#    #+#             */
/*   Updated: 2025/04/16 12:02:58 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// gives me how much element i should allocate in the array of structs
int	double_array_size(char **str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (-1);
	while (str[i])
		i++;
	return (i);
}

// skip spaces in a string from an existing
// index and return where the index next should be
void	skip_spaces(int *i, char *str)
{
	if (!str)
		return ;
	while (str[(*i)] == ' ')
		(*i)++;
}

// splits each string and stores the variables in the array of structs
t_comm	*arrayallocator(char **arr, t_env *env)
{
	int		i;
	int		size;
	t_comm	*comms;

	i = 0;
	if (!arr)
		return (NULL);
	size = double_array_size(arr);
	if (size == -1)
		return (NULL);
	comms = (t_comm *)malloc((size + 1) * sizeof(t_comm));
	if (!comms)
		return (NULL);
	while (arr[i])
	{
		commandeparser(arr[i], &comms[i], env);
	  if (DEBUG_MODE)
		  print_t_comm(&comms[i]);
	  if (DBG_ENV)
		  print_t_env(&comms[i]);
		i++;
	}
	// Ensure the last element is properly null-terminated if required
	memset(&comms[i], 0, sizeof(t_comm));
	return (comms);
}
