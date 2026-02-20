/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbardet- <lbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:20:41 by lbardet-          #+#    #+#             */
/*   Updated: 2026/02/13 10:49:31 by lbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char *str)
{
	printf("\n%s", str);
}

void	cd(char *arg)
{
	char	oldcwd[1024];

	getcwd(oldcwd, sizeof(oldcwd)); // reproduit pwd
	if (!arg || ft_strncmp(arg, "~", 1) == 0)
		arg = getenv("HOME");
	
}