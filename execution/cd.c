/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 02:05:33 by amabbadi          #+#    #+#             */
/*   Updated: 2025/04/14 02:05:34 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd(char *path, t_env *e)
{
	if (!path)
	{
		while (e)
		{
			if (e->key && !ft_strcmp(e->key, "HOME") && e->value)
			{
				chdir(e->value);
				break ;
			}
			e = e->next;
		}
	}
	else if (chdir(path))
		return (perror("Error in cd"), -1);
	return (0);
}