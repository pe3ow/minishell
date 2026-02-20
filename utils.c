/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbardet- <lbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 23:34:58 by leauvray          #+#    #+#             */
/*   Updated: 2026/02/13 09:53:06 by lbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strljoin(char const *s1, int start, int end)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(end - start + 1);
	if (!result)
		return (NULL);
	while (start < end)
	{
		result[i] = s1[start];
		i++;
		start++;
	}
	result[i] = 0;
	return (result);
}

void	free_tab(char **str_tab)
{
	int	i;

	i = 0;
	while (str_tab[i])
	{
		free(str_tab[i]);
		i++;
	}
	free(str_tab);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t'
		|| c == '\n' || c == '\v'
		|| c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	count_words(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && isspace(str[i]))
			i++;
		if (str[i])
		{
			count++;
			while (str[i] && !isspace(str[i]))
				i++;
		}
	}
	count++;
	return (count);
}
