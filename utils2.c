/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbardet- <lbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:05:21 by lbardet-          #+#    #+#             */
/*   Updated: 2026/02/24 19:10:57 by lbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *str)
{
	int	i;
	int	dquote;
	int	squote;

	dquote = 0;
	squote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			squote++;
		if (str[i] == '"')
			dquote++;
		i++;
	}
	if (dquote % 2 != 0)
		return (1);
	if (squote % 2 != 0)
		return (2);
	return (0);
}

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	set_env(t_env **env, char *key, char *value)
{
	t_env	*tmp;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (1);
	tmp = *env;
	while (tmp)
	{
		if (strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = strdup(value);
			return (0);
		}
		tmp = tmp->next;
	}
	new->key = strdup(key);
	new->value = strdup(value);
	new->next = *env;
	*env = new;
	return (0);
}
