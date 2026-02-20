/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbardet- <lbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:05:21 by lbardet-          #+#    #+#             */
/*   Updated: 2026/02/19 23:09:26 by lbardet-         ###   ########.fr       */
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
