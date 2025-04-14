/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hollyparser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 02:09:12 by azahid            #+#    #+#             */
/*   Updated: 2025/04/14 06:26:44 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_env_value(char *key, t_env *env) {
    while (env) {
        if (ft_strcmp(env->key, key) == 0)
            return env->value;
        env = env->next;
    }
    return ""; // not found => empty string
}

int expander_count(char *wrd, t_env *env) {
    int i = 1; // Start after the $
    char var[256] = {0};
    int vi = 0;

    // Extract the variable name (alphanumeric or '_')
    while (wrd[i] && (isalnum(wrd[i]) || wrd[i] == '_')) {
        var[vi++] = wrd[i++];
    }
    var[vi] = '\0';

    char *val = get_env_value(var, env);
    if (!val)
        return 0;

    int len = 0;
    while (val[len])
        len++;

    return len;
}
int is_squote(char c){
  return (c == '\'');
}
int is_dquote(char c){
  return (c == '\"');
}

int has_unbalanced_quotes(char *wrd) {
    int i = 0, sq = 0, dq = 0;

    while (wrd[i]) {
        if (wrd[i] == '\'') sq++;
        else if (wrd[i] == '"') dq++;
        i++;
    }
    return (sq % 2 || dq % 2);
}

int handle_squotes(const char *wrd, int *i) {
    int count = 0;
    (*i)++; // skip opening '
    while (wrd[*i] && wrd[*i] != '\'') {
        count++;
        (*i)++;
    }
    if (wrd[*i]) (*i)++; // skip closing '
    return count;
}

int handle_dquotes(const char *wrd, int *i, t_env *env) {
    int count = 0;
    (*i)++; // skip opening "
    while (wrd[*i] && wrd[*i] != '"') {
        if (wrd[*i] == '$' && wrd[*i + 1]) {
            count += expander_count((char *)(wrd + *i), env);
            (*i)++; // skip $
            while (isalnum(wrd[*i]) || wrd[*i] == '_')
                (*i)++;
        } else {
            count++;
            (*i)++;
        }
    }
    if (wrd[*i]) (*i)++; // skip closing "
    return count;
}

int cw(char *wrd, t_env *env) {
    int i = 0;
    int count = 0;

    if (has_unbalanced_quotes(wrd))
        return -1;

    while (wrd[i]) {
        if (wrd[i] == '\'')
            count += handle_squotes(wrd, &i);
        else if (wrd[i] == '"')
            count += handle_dquotes(wrd, &i, env);
        else if (wrd[i] == '$' && wrd[i + 1]) {
            count += expander_count(wrd + i, env);
            i++;
            while (isalnum(wrd[i]) || wrd[i] == '_')
                i++;
        } else {
            count++;
            i++;
        }
    }

    return count;
}


int expand_variable(char *src, t_env *env, char *dest, int *si) {
    int i = 1;
    char var[256] = {0};
    int vi = 0;

    while (src[i] && (isalnum(src[i]) || src[i] == '_')) {
        var[vi++] = src[i++];
    }
    var[vi] = '\0';

    char *val = get_env_value(var, env); 
    int len = 0;
    if (val) {
        while (val[len]) {
            dest[len] = val[len];
            len++;
        }
    }

    *si += vi + 1; // skip $ + var name
    return len;
}

void fill_word(char *dest, char *src, t_env *env) {
    int si = 0;  // src index
    int di = 0;  // dest index

    while (src[si]) {
        if (src[si] == '\'') {
            si++; // skip opening '
            while (src[si] && src[si] != '\'')
                dest[di++] = src[si++];
            if (src[si]) si++; // skip closing '
        }
        else if (src[si] == '"') {
            si++; // skip opening "
            while (src[si] && src[si] != '"') {
                if (src[si] == '$' && src[si + 1]) {
                    di += expand_variable(src + si, env, dest + di, &si);
                } else {
                    dest[di++] = src[si++];
                }
            }
            if (src[si]) si++; // skip closing "
        }
        else if (src[si] == '$' && src[si + 1]) {
            di += expand_variable(src + si, env, dest + di, &si);
        }
        else {
            dest[di++] = src[si++];
        }
    }

    dest[di] = '\0';
}

char *parser(char *str,t_env *env){
  int countw;

  if (!str)
    return NULL;
  countw = cw(str,env);
  if (countw == -1)
    return NULL;
  char *res = malloc(sizeof(char) *(countw + 1));
  if (!res)
    return NULL;
  fill_word(res, str, env);
  return res;
}
