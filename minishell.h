/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:51:00 by azahid            #+#    #+#             */
/*   Updated: 2025/04/07 23:27:59 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_ints
{
	int				i;
	struct s_ints	*next;
}					t_ints;

typedef struct s_chars
{
	char			*str;
	struct s_chars	*next;
	int				type;
}					t_chars;


// struct holding every thing about a single commande after splted by pipe
typedef struct s_commande
{
	// parsed commande with the right attribute;
	char			**p_com;
	// commande from the stdin
	char			*commande;
	t_chars			*redirections;
	// infile
	t_chars			*heardoc;
}					t_comm;

void				parserlexer(char *input);
t_comm				*arrayallocator(char **arr);
void				commandeparser(char *arr, t_comm *com);

/*			UTILITIES			*/

char				*ft_strnstr(const char *str, const char *t, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				**ft_split(char const *s, char c);
size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *s1);
char				*ft_strchr(char *s, int c);
char				*ft_strndup(const char *s, size_t n);
void				*ft_memset(void *s, int c, size_t n);
int					ft_strcmp(char *s1, char *s2);

void				get_full_command(t_comm *com, char *prompt);
void				fill_inputs(t_comm *com);
void				fill_outputs(t_comm *com);
int					ft_isspace(char c);
void loader(char *str,t_comm *comm);
void	push_to_list(t_chars **head, char *str, int typ);

/*		DEBUGGING		*/

void				print_t_comm(t_comm *cmd);

#endif
