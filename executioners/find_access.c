/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 03:27:54 by azahid            #+#    #+#             */
/*   Updated: 2025/03/26 03:50:01 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**parse_envp(char *envp[])
{
	int		i;
	char	**sp;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != NULL)
		{
			sp = ft_split(envp[i] + 5, ':');
			if (!sp)
				return (NULL);
			return (sp);
		}
		i++;
	}
	return (NULL);
}

char	*joined(char *commande, char *sp)
{
	char	*com;
	char	*joinedpath;

	com = ft_strjoin("/", commande);
	if (!com)
		return (NULL);
	joinedpath = ft_strjoin(sp, com);
	if (!joinedpath)
		return (free(com), NULL);
	return (free(com), joinedpath);
}

char	*find_access(char *path[], char *commande)
{
	char	**sp;
	char	*joinedpath;
	int		i;

	i = 0;
	sp = parse_envp(path);
	if (!sp)
		return (NULL);
	while (sp[i])
	{
		joinedpath = joined(commande, sp[i]);
		if (!joinedpath)
			return (NULL);
		if (++i && !(access(joinedpath, F_OK | X_OK)))
			return (joinedpath);
		free(joinedpath);
	}
	if (!access(commande, F_OK | X_OK))
		return (ft_strdup(commande));
	return (NULL);
}
