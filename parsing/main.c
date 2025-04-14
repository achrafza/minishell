/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 20:43:43 by azahid            #+#    #+#             */
/*   Updated: 2025/04/12 03:10:50 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

int     g_signal;

void    handle_sigint(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

char *get_prompt(void)
{
    char cwd[PATH_MAX];
    char *last;
    char prompt[128];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        last = strrchr(cwd, '/');
        if (last && *(last + 1))
            last++;
        else
            last = cwd;
        snprintf(prompt, sizeof(prompt), "\x1b[1;35m[minihell]: \x1b[36m~%s\x1b[0m ", last);
    }
    else
        snprintf(prompt, sizeof(prompt), "\x1b[1;35m[minihell]:~ \x1b[0m");
    return strdup(prompt);
}

void    handle_sigquit(int sig)
{
    (void)sig;
}

void    setup_signals(void)
{
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, handle_sigquit);
    signal(SIGTERM, SIG_IGN);
}

int main(int ac, char **av, char *envp[])
{
    char    *input;
    t_env   *env;
    char    *prompt;

    (void)ac;
    (void)av;
    (void)envp;
	if (!envp || !*envp) 
	{
		t_env *new_env = malloc(sizeof(t_env));
		new_env->key = ft_strdup("PATH");
		new_env->value = ft_strdup(DEFAULT_PATH); 
		new_env->next = NULL;
		env = new_env; 
	}
	else
    	env = env_list_from_array(envp);
    increment_shlvl(env);
    setup_signals();
    read_history("history.txt");
    while (1337)
    {
        prompt = get_prompt();
        input = readline(prompt);
        free(prompt);
        if (input == NULL) break;
        if (*input)
            add_history(input);
        parserlexer(input, envp, env);
        free(input);
    }
    write(1, "exit\n", 5);
    rl_clear_history();
    return (0);
}