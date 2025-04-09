/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_com_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:18:10 by azahid            #+#    #+#             */
/*   Updated: 2025/04/09 02:47:07 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>

int	is_redirection(char c)
{
	return (c == '<' || c == '>');
}

//"      ls  -a>out<ouss"
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
			else
      {
        count++;
        while(s[i] &&!ft_isspace(s[i]) && !is_redirection(s[i]))
          i++;
      }
    }
	}
	return (count);
}

unsigned int ft_wdlen(char *str){
  int i = 0;
  while(str[i] && !ft_isspace(str[i]) && !is_redirection(str[i]))
    i++;
  return i;
}

char	**allocate(char **arr, char *str, int cc)
{
	int	i;
  int wrdlen;
  int j = 0;
  int k = 0;
  char *s;

  cc+=1-1;
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
    else {
      wrdlen = ft_wdlen(str + i);
      s= (char *)malloc(wrdlen+1);
      arr[j] = s;
      while(str[i] && !is_redirection(str[i]) && k < wrdlen){
        arr[j][k] = str[i++];
        k++;
      }
      arr[j][k] = 0;
      k = 0;
      j++;
    }
	}
  arr[j]=NULL;
  return arr;
}
char	**p_com_split(char *str)
{
	int		count;
	char	**res;

	count = count_checker(str);
  printf("\n%d\n",count);
	res = (char **)malloc((count + 1) * sizeof(char *));
  res = allocate(res, str, count);
  return res;
}
