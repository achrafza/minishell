/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_com_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:18:10 by azahid            #+#    #+#             */
/*   Updated: 2025/04/15 01:42:44 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>

int	is_redirection(char c)
{
	return (c == '<' || c == '>');
}

int	isquote(char c)
{
	return (c == '\'' || c == '\"');
}

int	count_checker(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i] && !ft_isspace(s[i]))
		{
			if (is_redirection(s[i]))
			{
				i++;
				while (s[i] && ft_isspace(s[i]))
					i++;
				while (s[i] && !ft_isspace(s[i]) && !is_redirection(s[i]))
					i++;
			}
			else if (s[i] && isquote(s[i]))
			{
				i++;
				count++;
				while (s[i] && !isquote(s[i]))
					i++;
				if (!s[i])
					// exjt Syntax error
					return (0);
				else
					i++;
			}
			else
			{
				count++;
				while (s[i] && !ft_isspace(s[i]) && !is_redirection(s[i]))
					i++;
			}
		}
	}
	return (count);
}

int	ft_wdlen(char *str)
{
	int	i;

	i = 0;
	if (isquote(str[i]))
	{
		i++;
		while (str[i] && !isquote(str[i]))
			i++;
		if (!str[i])
			return (-1);
		return (i + 1);
	}
	while (str[i] && !ft_isspace(str[i]) && !is_redirection(str[i]))
		i++;
	return (i);
}

//"      ls   "     out     "
char	*alloc_word(char *des, int len, char *src)
{
	int	i;

	i = 0;
	while (src[i] && i < len)
	{
		des[i] = src[i];
		i++;
	}
	des[i] = 0;
	return (des);
}
char	**allocate(char **arr, char *str, int cc)
{
	int	i;
	int	wrdlen;
	int	j;

	j = 0;
	cc += 1 - 1;
	i = 0;
	while (str[i])
	{
		while (ft_isspace(str[i]))
			i++;
		if (is_redirection(str[i]))
		{
			i++;
			while (str[i] && ft_isspace(str[i]))
				i++;
			while (str[i] && !ft_isspace(str[i]) && !is_redirection(str[i]))
				i++;
		}
		else if (str[i])
		{
			wrdlen = ft_wdlen(str + i);
			if (wrdlen == -1)
				// free all the past array
				return (NULL);
			arr[j] = (char *)malloc(wrdlen + 1);
			arr[j] = alloc_word(arr[j], wrdlen, str + i);
			i += wrdlen;
			j++;
		}
	}
	arr[j] = NULL;
	return (arr);
}
char	**p_com_split(char *str)
{
	int		count;
	char	**res;
  if(!str)
    return NULL;
	count = count_checker(str);
	res = (char **)malloc((count + 1) * sizeof(char *));
	res = allocate(res, str, count);
	return (res);
}
