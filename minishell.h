/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 00:51:00 by azahid            #+#    #+#             */
/*   Updated: 2025/04/10 01:46:41 by azahid           ###   ########.fr       */
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

# define DEFAULT_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

typedef struct s_ints
{
	int				i;
	struct s_ints	*next;
}					t_ints;

typedef struct s_env
{
	char			*env;
	struct s_env	*next;
}					t_env;

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
	// env
	t_env			*env;
}					t_comm;

void				parserlexer(char *input, char **envp);
t_comm				*arrayallocator(char **arr, t_env *env);
void				commandeparser(char *arr, t_comm *com, t_env *envp);

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
void				loader(char *str, t_comm *comm);
void				push_to_list(t_chars **head, char *str, int typ);
char				**p_com_split(char *s);
int					isquote(char c);
int					is_redirection(char c);
int					double_array_size(char **str);

/*		DEBUGGING		*/

void				print_t_comm(t_comm *cmd);
/*		FREE			*/
void				free1d(void *array);
void				free2d(char **array);
void				free_commande(t_comm *com);
void				free_all_commande(t_comm *comms, int size);
void				free_env(t_env *head);

/*	env   */
char				**parse_envp(char *envp[]);
char				*joined(char *commande, char *sp);
char				*find_access(char *path[], char *commande);

t_env				*push_env(t_env *head, char **new_env);
t_env				*env_list_from_array(char **env);
t_env				*create_env_node(char *env_str);

#endif
