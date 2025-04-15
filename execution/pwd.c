/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 02:06:25 by amabbadi          #+#    #+#             */
/*   Updated: 2025/04/14 02:06:26 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*pwd(void)
{
	char	buff[PATH_MAX];
	char	*path;

	getcwd(buff, sizeof(buff));
	path = ft_strdup(buff);
	if (!path)
		return (NULL);
	return (path);
}
