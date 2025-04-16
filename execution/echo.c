/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 02:05:43 by amabbadi          #+#    #+#             */
/*   Updated: 2025/04/14 02:05:45 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_n(const char *str)
{
	int	i;

	if (!str || str[0] != '-')
		return (0);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (i > 1);
}

int	echo(t_comm *com)
{
	int	i;
	int	no_nl;
	int	first;

	i = 1;
	no_nl = 0;
	if (!com || !com->p_com || !com->p_com[0])
	{
		if (com && com->env)
			com->env->exit_status = 0;
		printf("\n");
		return (0);
	}
	while (com->p_com[i] && is_n(com->p_com[i]))
	{
		no_nl = 1;
		i++;
	}
	first = 1;
	while (com->p_com[i])
	{
		if (!first)
			printf(" ");
		if (com->p_com[i])
			printf("%s", com->p_com[i]);
		first = 0;
		i++;
	}
	if (!no_nl)
		printf("\n");
	if (com && com->env)
		com->env->exit_status = 0;
	return (0);
}
