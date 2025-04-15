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
// string
// ls -a > hello < hee

int	loader(char *str, t_comm *comm,t_env *env)
{
	int		i;
	int		j;
	char	*sub;
	int		len;
  char  quote;
  (void)(env);

	i = 0;
	j = 0;
	sub = NULL;
	len = ft_strlen(str);
	while (str[i])
	{
		while (str[i] && !is_redirection(str[i]) && !isquote(str[i]))
			i++;
		if (isquote(str[i]))
		{
			i++;
			while (str[i] && !isquote(str[i]))
				i++;
			i++;
		}
    else if (str[i] && str[i] == str[i+1] && str[i] == '<')
    {
      i+=2;
      if (is_redirection(str[i]) || str[i] == '|'){
        perror("Syntax error");
        return -1;
      }
			while (str[i] && ft_isspace(str[i]))
				i++;
			j = i;
      if (isquote(str[i])){
        quote = str[j++];
        while(str[j] && str[j] != quote)
          j++;
        if(str[j]) j++;
      }
      else{
			while (str[j] && !ft_isspace(str[j]) && !is_redirection(str[j]))
				j++;}
			while (str[j] && !ft_isspace(str[j]) && !is_redirection(str[j]))
				j++;
			if (j > i)
			{
				sub = ft_substr(str, i, j - i);
				if (!sub)
					// we should handle the free all elements and quit code
					return -1;
        sub = parser(sub, env);
				push_to_list(&comm->redirections, sub, 2);
			}
			// loader(str + j,comm);
			i = j;
    }
    else if(str[i] && str[i] == str[i+1] && str[i] == '>')
    {
      i+=2;
      if (is_redirection(str[i]) || str[i] == '|'){
        perror("Syntax error");
        return -1;
      }

			while (str[i] && ft_isspace(str[i]))
				i++;
			j = i;      
      if (isquote(str[i])){
        quote = str[j++];
        while(str[j] && str[j] != quote)
          j++;
        if(str[i]) j++;
      }
      else{
			while (str[j] && !ft_isspace(str[j]) && !is_redirection(str[j]))
				j++;}
			while (str[j] && !ft_isspace(str[j]) && !is_redirection(str[j]))
				j++;
			if (j > i)
			{
				sub = ft_substr(str, i, j - i);
				if (!sub)
					// we should handle the free all elements and quit code
					return -1;
        sub = parser(sub, env);
				push_to_list(&comm->redirections, sub, 3);
			}
			// loader(str + j,comm);
			i = j;
    }
		else if (str[i] == '<')
		{
			i++;
      if (is_redirection(str[i]) || str[i] == '|'){
        perror("Syntax error");
        return -1;
      }
			while (str[i] && ft_isspace(str[i]))
				i++;
			j = i;
      if (isquote(str[i])){
        quote = str[j++];
        while(str[j] && str[j] != quote)
          j++;
        if(str[j]) j++;
      }
      else{
			while (str[j] && !ft_isspace(str[j]) && !is_redirection(str[j]))
				j++;
      }	
      while (str[j] && !ft_isspace(str[j]) && !is_redirection(str[j]))
				j++;
			if (j > i)
			{
				sub = ft_substr(str, i, j - i);
				if (!sub)
					// we should handle the free all elements and quit code
					return -1;
        sub = parser(sub, env);
				push_to_list(&comm->redirections, sub, 0);
			}
			// loader(str + j,comm);
			i = j;
		}
		else if (str[i] == '>')
		{
			i++;
      if (is_redirection(str[i]) || str[i] == '|'){
        perror("Syntax error");
        return -1;
      }
			while (str[i] && ft_isspace(str[i]))
				i++;
			j = i;
      if (isquote(str[i])){
        quote = str[j++];
        while(str[j] && str[j] != quote)
          j++;
        if(str[j]) j++;
      }
      else{
			while (str[j] && !ft_isspace(str[j]) && !is_redirection(str[j]))
				j++;
      }
			while (str[j] && !ft_isspace(str[j]) && !is_redirection(str[j]))
				j++;
			if (j > i)
			{
				sub = ft_substr(str, i, j - i);
				if (!sub)
					// we should handle the free all elements and quit code
					return -1;
        sub = parser(sub, env);
				push_to_list(&comm->redirections, sub, 1);
			}
			// loader(str + j,comm);
			i = j;
		}
		else if (i < len - 1)
			i++;
	}
  return 0;
}
