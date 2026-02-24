/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbardet- <lbardet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 10:20:41 by lbardet-          #+#    #+#             */
/*   Updated: 2026/02/24 19:35:10 by lbardet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
}

int	cd(t_cmd *cmd, char **env, t_env **env_list)
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
	set_env(env_list, "OLDPWD", oldpwd);
	set_env(env_list, "PWD", newpwd);
	return (free(oldpwd), free(newpwd), 0);
}

int	pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	export(t_cmd *cmd, char **env)
{
	int	i;

	if (!cmd->args[1])
		return (print_env(*env), 0);
	i = 1;
	while (cmd->args[i])
	{
		if (strchr(cmd->args[i], '='))
			set_env(env, cmd->args[i], strchr(cmd->args[i], '=') + 1);
		else
			set_env(env, cmd->args[i], get_env_value(*env, cmd->args[i]));
		i++;
	}
	return (0);
}

int	unset(t_cmd *cmd, char **env)
{
	int	i;

	if (!cmd->args[1])
		return (printf("unset: not enough arguments\n"), 1);
	i = 1;
	while (cmd->args[i])
	{
		unset_env(env, cmd->args[i]);
		i++;
	}
	return (0);
}
