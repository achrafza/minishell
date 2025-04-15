/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 03:27:54 by azahid            #+#    #+#             */
/*   Updated: 2025/04/14 08:16:34 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**parse_envp(t_env *e)
{
	char	**sp;

	while (e)
	{
		if (e->key && !ft_strcmp(e->key, "PATH"))
		{
			if (!e->value)
				return (NULL);
			sp = ft_split(e->value, ':');
			if (!sp)
				return (NULL);
			return (sp);
		}
		e = e->next;
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
		return (NULL);
	return (joinedpath);
}

char	*find_access(t_comm *com)
{
	char	**sp;
	char	*joinedpath;
	int		i;

	i = 0;
	sp = parse_envp(com->env);
	while (sp && sp[i] && com->p_com && com->p_com[0])
	{
		joinedpath = joined(com->p_com[0], sp[i]);
		if (!joinedpath)
			return (NULL);
		if (++i && !(access(joinedpath, F_OK | X_OK)))
			return (joinedpath);
		free(joinedpath);
	}
	if (com->p_com && !access(com->p_com[0], F_OK | X_OK))
		return (com->p_com[0]);
	return (ft_strdup(com->p_com[0]));
}

char	**createargs(t_comm *com)
{
	char	*first;

	first = find_access(com);
	if (!first)
	{
		return (NULL);
	}
	/*5atar : segv*/
	// free(com->p_com[0]);
	com->p_com[0] = first;
	return (com->p_com);
}
