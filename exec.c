/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbardet- <lbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 21:33:20 by lbardet-          #+#    #+#             */
/*   Updated: 2026/02/24 20:19:49 by lbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	monitor(t_cmd **cmd_array, t_token **args, char **envp)
{
	if (is_builtin(args, cmd_array[0]))
		return (exec_builtin(args, cmd_array[0]));
	else
		return (exec_external(args, cmd_array[0], envp));
}

void	exec_builtin(t_token **args, char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (echo(args[0]));
	else if (ft_strcmp(cmd, "cd") == 0)
		return (cd);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (pwd);
	else if (ft_strcmp(cmd, "export") == 0)
		return (export);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (unset);
	else if (ft_strcmp(cmd, "env") == 0)
		return (env);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (builtin_exit);
	else
		return (NULL);
}

int	
