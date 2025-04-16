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
	static char	prev_dir[PATH_MAX];
	static char	new_dir[PATH_MAX];

	if (getcwd(new_dir, sizeof(new_dir)) == NULL)
		return (perror("cd: error getting current directory"), -1);
	if (!path)
	{
		while (e)
		{
			if ((e->key && (!ft_strcmp(e->key, "HOME") || !ft_strcmp(e->key,
							"~"))) && e->value)
			{
				if (chdir(e->value) != 0)
					return (perror("cd"), -1);
				// Update directory history
				if (prev_dir[0] != '\0')
					strncpy(prev_dir, new_dir, sizeof(prev_dir) - 1);
				return (0);
			}
			e = e->next;
		}
		fprintf(stderr, "cd: HOME not set\n");
		return (-1);
	}
	if (ft_strcmp(path, ".") == 0)
		return (0);
	if (ft_strcmp(path, "~") == 0)
	{
		while (e)
		{
			if ((e->key && (!ft_strcmp(e->key, "HOME") || !ft_strcmp(e->key,
							"~"))) && e->value)
			{
				if (chdir(e->value) != 0)
					return (perror("cd"), -1);
				// Update directory history
				if (prev_dir[0] != '\0')
					strncpy(prev_dir, new_dir, sizeof(prev_dir) - 1);
				return (0);
			}
			e = e->next;
		}
		fprintf(stderr, "cd: HOME not set\n");
		return (-1);
	}
	if (ft_strcmp(path, "/") == 0)
	{
		if (chdir("/") != 0)
			return (perror("cd"), -1);
		if (prev_dir[0] != '\0')
			strncpy(prev_dir, new_dir, sizeof(prev_dir) - 1);
		return (0);
	}
	if (ft_strcmp(path, "-") == 0)
	{
		if (prev_dir[0] == '\0')
		{
			fprintf(stderr, "cd: no previous directory\n");
			return (-1);
		}
		if (chdir(prev_dir) != 0)
			return (perror("cd"), -1);
		printf("%s\n", prev_dir);
		strncpy(prev_dir, new_dir, sizeof(prev_dir) - 1);
		return (0);
	}
	if (access(path, F_OK) != 0)
		return (perror("cd"), -1);
	if (chdir(path) != 0)
		return (perror("cd"), -1);
	if (prev_dir[0] != '\0')
		strncpy(prev_dir, new_dir, sizeof(prev_dir) - 1);
	else
		strncpy(prev_dir, new_dir, sizeof(prev_dir) - 1);
	return (0);
}
