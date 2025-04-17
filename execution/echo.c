/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 02:05:43 by amabbadi          #+#    #+#             */
/*   Updated: 2025/04/16 13:52:16 by azahid           ###   ########.fr       */
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
	int no_nl;
	int first;
	t_chars *p;

	if (!com || !com->p_com)
	{
		if (com && com->env)
			com->env->exit_status = 0;
		printf("\n");
		return (0);
	}

	no_nl = 0;
	p = com->p_com->next;
	// Skip all -n flags
	while (p && p->str && is_n(p->str))
	{
		no_nl = 1;
		p = p->next;
	}

	first = 1;
	while (p && p->str)
	{
		if (!first)
			printf(" ");
		printf("%s", p->str);
		first = 0;
		p = p->next;
	}

	if (!no_nl)
		printf("\n");
	if (com && com->env)
		com->env->exit_status = 0;
	return (0);
}