/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:09:58 by azahid            #+#    #+#             */
/*   Updated: 2025/04/15 08:00:53 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	int				i;
	unsigned int	l;

	l = ft_strlen(s);
	if (s == NULL)
		return (NULL);
	if (len > l - start)
		len = l - start;
	if (l <= start)
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (len-- && *(s + start))
	{
		*(str + i) = *(s + start);
		i++;
		s++;
	}
	*(str + i) = 0;
	return (str);
}

static int	skip_quoted_section(char *str, int i)
{
	char	quote;

	quote = str[i++];
	while (str[i] && str[i] != quote)
		i++;
	if (str[i])
		i++;
	return (i);
}

static int	get_token_end(char *str, int start)
{
	int		j;
	char	quote;

	j = start;
	if (isquote(str[j]))
	{
		quote = str[j++];
		while (str[j] && str[j] != quote)
			j++;
		if (str[j])
			j++; // Include closing quote
	}
	else
	{
		while (str[j] && !ft_isspace(str[j]) && !is_redirection(str[j]))
			j++;
	}
	while (str[j] && !ft_isspace(str[j]) && !is_redirection(str[j]))
		j++;
	return (j);
}

static int	check_syntax_error(char *str, int i)
{
	if (is_redirection(str[i]) || str[i] == '|')
	{
		perror("Syntax error");
		return (-1);
	}
	return (0);
}

static int	process_redirection(char *str, int *i, t_comm *comm, t_env *env,
		int redir_type)
{
	int		j;
	char	*sub;

	if (check_syntax_error(str, *i))
		return (-1);
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
	j = get_token_end(str, *i);
	if (j > *i)
	{
		sub = ft_substr(str, *i, j - *i);
		if (!sub)
			return (-1);
		sub = parser(sub, env);
		if (!sub)
			return (-1);
		push_to_list(&comm->redirections, sub, redir_type);
	}
	*i = j;
	return (0);
}

int	loader(char *str, t_comm *comm, t_env *env)
{
	int i;
	int len;

	(void)(env);
	i = 0;
	len = ft_strlen(str);
	while (str && str[i])
	{
		while (str[i] && !is_redirection(str[i]) && !isquote(str[i]))
			i++;
		if (isquote(str[i]))
			i = skip_quoted_section(str, i);
		else if (str[i] && str[i] == str[i + 1] && str[i] == '<')
		{
			i += 2;
			if (process_redirection(str, &i, comm, env, 2) < 0)
				return (-1);
		}
		else if (str[i] && str[i] == str[i + 1] && str[i] == '>')
		{
			i += 2;
			if (process_redirection(str, &i, comm, env, 3) < 0)
				return (-1);
		}
		else if (str[i] == '<')
		{
			i++;
			if (process_redirection(str, &i, comm, env, 0) < 0)
				return (-1);
		}
		else if (str[i] == '>')
		{
			i++;
			if (process_redirection(str, &i, comm, env, 1) < 0)
				return (-1);
		}
		else if (i < len - 1)
			i++;
	}
	return (0);
}