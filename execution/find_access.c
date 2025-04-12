/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_access.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 03:27:54 by azahid            #+#    #+#             */
/*   Updated: 2025/04/12 02:34:27 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**parse_envp(t_env *e)
{
	int		i;
	char	**sp;

	i = 0;
  t_env *envp = e;
	while (envp->next)
	{
		if (ft_strnstr(envp->env, "PATH=", 5) != NULL)
		{
			sp = ft_split(envp->env + 5, ':');
			if (!sp)
				return (NULL);
			return (sp);
		}
		envp=envp->next;
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

char	*find_access(t_comm *com)
{
	char	**sp;
	char	*joinedpath;
	int		i;

	i = 0;
	sp = parse_envp(com->env);
	// if (!sp)
	// 	return (NULL);
	while (sp && sp[i])
	{
		joinedpath = joined(com->p_com[0], sp[i]);
		if (!joinedpath)
		return (NULL);
		if (++i && !(access(joinedpath, F_OK | X_OK)))
		return (joinedpath);
		free(joinedpath);
	}
	if (!access(com->p_com[0], F_OK | X_OK))
		return (com->p_com[0]);
	return (NULL);
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
  	//free(com->p_com[0]);
  	com->p_com[0] = first;
	return com->p_com;
}
