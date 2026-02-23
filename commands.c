/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbardet- <lbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:20:41 by lbardet-          #+#    #+#             */
/*   Updated: 2026/02/23 22:12:38 by lbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char *str)
{
	printf("%s", str);
}

int	cd(t_cmd *cmd, char **env)
{
	char	*path;
	char	*oldpwd;
	char	*newpwd;

	if (cmd->args[2])
		return (printf("cd: too many arguments\n"), 1);
	if (!cmd->args[1])
		path = get_env_value(*env, "HOME");
	else if (strcmp(cmd->args[1], "-") == 0)
		path = get_env_value(*env, "OLDPWD");
	else
		path = cmd->args[1];
	if (!path)
		return (printf("cd: HOME not set\n"), 1);
	oldpwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		perror("cd");
		free(oldpwd);
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	set_env(env, "OLDPWD", oldpwd);
	set_env(env, "PWD", newpwd);
	return (free(oldpwd), free(newpwd), 0);
}
