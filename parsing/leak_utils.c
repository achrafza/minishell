/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leak_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 02:07:00 by amabbadi          #+#    #+#             */
/*   Updated: 2025/04/14 02:07:01 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free1d(void *array)
{
	if (array != NULL)
		free(array);
}

void	free2d(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_chars(t_chars *list)
{
	t_chars	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->str);
		free(tmp);
	}
}

void	free_ints_list(t_ints *head)
{
	t_ints	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}

void	free_commande(t_comm *com)
{
	int	i;

	if (!com)
		return ;
	if (com->p_com)
	{
		for (i = 0; com->p_com[i]; i++)
			free(com->p_com[i]);
		free(com->p_com);
	}
	if (com->commande)
		free(com->commande);
	if (com->redirections)
		free_chars(com->redirections);
	if (com->heardoc)
	{
		free_chars(com->heardoc);
	}
	// free(com);
}

void	free_all_commande(t_comm *comms, int size)
{
	int	i;

	if (!comms)
		return ;
	i = 0;
	while (i < size)
	{
		free_commande(&comms[i]);
		i++;
	}
	free(comms);
}

void	free_env(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->key);
		free(head->value);
		free(head);
		head = tmp;
	}
}
