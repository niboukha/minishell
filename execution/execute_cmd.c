/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 11:23:26 by niboukha          #+#    #+#             */
/*   Updated: 2023/08/07 20:23:09 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_access(DIR *dir, char *cmd)
{
	if (dir)
	{
		g_data->exit_code = 126;
		exit_code(DIR_ERR, cmd);
		closedir(dir);
		exit(g_data->exit_code);
	}
	if (access(cmd, F_OK) == -1)
	{
		g_data->exit_code = CMD_NOT_FOUND;
		exit_code(ACCESS_CMD, cmd);
		exit(g_data->exit_code);
	}
	if (access(cmd, X_OK | F_OK) == -1)
	{
		g_data->exit_code = CMD_NOT_EXECUTABLE;
		exit_code(PERM_DEN, cmd);
		exit(g_data->exit_code);
	}
}

void	execve_function(t_minishell *minishell)
{
	char	*cmd;
	char	**env;
	DIR		*dir;

	cmd = valid_cmd(minishell);
	env = convert_to_env();
	dir = opendir(cmd);
	if (ft_strchr(cmd, '/'))
		check_access(dir, cmd);
	g_data->exit_code = CMD_NOT_FOUND;
	if (!ft_strchr(cmd, '/'))
	{
		exit_code(CMD_NOT_FND, cmd);
		exit(g_data->exit_code);
	}
	execve(cmd, minishell->cmd, env);
	if (!minishell->path)
	{
		g_data->exit_code = CMD_NOT_FOUND;
		exit_code(ACCESS_CMD, cmd);
		exit(g_data->exit_code);
	}
	exit_code(CMD_NOT_FND, cmd);
	exit(g_data->exit_code);
}
