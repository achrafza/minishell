/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserlexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:50:34 by azahid            #+#    #+#             */
/*   Updated: 2025/04/07 17:53:38 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*still unfinished for now , but sets the whole struct to 0 for future calls ,
	then fills
the struct based on their existence . for now the whole 4 args in the struct are filled*/

void	parserlexer(char *input)
{
  int size = 0;
  char **str = ft_split(input, '|');
  t_comm *coms = arrayallocator(str);
  (void)(coms);

  size = double_array_size(str);
  free_all_commande(coms, size);
  // free_commande(coms);
  free2d(str);
  return ;
}
