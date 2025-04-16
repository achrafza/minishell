/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amabbadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 02:06:07 by amabbadi          #+#    #+#             */
/*   Updated: 2025/04/14 02:06:07 by amabbadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void env(t_comm *cmd)
{
    t_env *env;

    if (!cmd || !cmd->p_com || !cmd->p_com[0])
        return ;
    if (cmd->p_com[1])
    {
        printf("env: too many arguments\n");
        return ;
    }
    env = cmd->env;
    while (env)
    {
        if (env->key && env->value)
            printf("%s=%s\n", env->key, env->value);
        env = env->next;
    }
}