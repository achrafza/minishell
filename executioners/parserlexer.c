/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserlexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:50:34 by azahid            #+#    #+#             */
/*   Updated: 2025/03/26 02:21:30 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


/*still unfinished for now , but sets the whole struct to 0 for future calls , then fills 
the struct based on their existence . for now the whole 4 args in the struct are filled*/

void    parserlexer(char *input)
{
    t_comm  com;

    ft_memset(&com, 0, sizeof(t_comm));
    get_full_command(&com, input);
    if (!com.commande)
        return;
    commandeparser(com.commande, &com);
    if (!com.p_com)
        return;
    fill_inputs(&com);
    fill_outputs(&com);

	print_t_comm(&com);
}