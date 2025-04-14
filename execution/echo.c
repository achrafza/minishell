/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 02:05:43 by amabbadi          #+#    #+#             */
/*   Updated: 2025/04/14 02:05:45 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int echo(char **input)
{
    if (!input || !input[0]) 
        return(printf("\n"), 0);
    int i = 1;
    if (input[1] && !ft_strcmp(input[1], "-n"))
        i++; 
    while (input[i])
    {
        printf("%s", input[i]);
        if (input[i + 1])
            printf(" ");
        i++;
    }
    if (!(input[1] && !ft_strcmp(input[1], "-n")))
        printf("\n");
    return 0;
}
