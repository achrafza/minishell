/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shshlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 02:06:34 by amabbadi          #+#    #+#             */
/*   Updated: 2025/04/14 02:06:37 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_digits(int n)
{
	int	count;

	count = 1;
	while (n >= 10)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	if (n < 0)
		return (NULL);
	len = count_digits(n);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = 0;
	while (len--)
	{
		str[len] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

void increment_shlvl(t_env *env)
{
    int   shlvl;
    char *tmp;

    while (env)
    {
        if (env->key && !strcmp(env->key, "SHLVL"))
        {
            shlvl = atoi(env->value);
            shlvl++;
            tmp = ft_itoa(shlvl);
            if (!tmp)
                return ;
            free(env->value);
            env->value = tmp;
            return ;
        }
        env = env->next;
    }
}