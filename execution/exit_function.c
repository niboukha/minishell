/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 08:58:30 by niboukha          #+#    #+#             */
/*   Updated: 2023/08/05 17:38:24 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	message_error3(t_error err, char *cmd)
{
	if (err == NUM_ARGS)
		ft_putendl_fd("minishell: No such file or directory", STDERR_FILENO);
	if (err == EXIT_A_ERR)
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
	if (err == PIPE_ERR)
		ft_putendl_fd("minishell: error in open pipe", STDERR_FILENO);
	if (err == FORK_ERR)
		ft_putendl_fd("minishell: error in fork", STDERR_FILENO);
	if (err == ACCESS_CMD)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
	if (err == ENV_ERR)
	{
		ft_putstr_fd("minishell: env: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
}

void	message_error2(t_error err, char *cmd)
{
	if (err == CMD_NOT_FND)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
	if (err == PERM_DEN)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": Permission denied", STDERR_FILENO);
	}
	if (err == HOME_NOT_SET)
		ft_putendl_fd("cd : HOME not set", STDERR_FILENO);
	if (err == OLDPWD_NOT_SET)
		ft_putendl_fd("cd : OLDPWD not set", STDERR_FILENO);
	if (err == CHDIR_ERR)
	{
		g_data->exit_code = 1;
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(" No such file or directory", STDERR_FILENO);
	}
}

void	message_error(t_error err, char *cmd)
{
	if (err == UNSET_ERR)
	{
		ft_putstr_fd("minishell: unset: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	}
	if (err == DIR_ERR)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": is a directory", STDERR_FILENO);
	}
	if (err == EXPORT_ERR)
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	}
	if (err == EXIT_N_A_R)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	}
}

void	exit_code(t_error err, char	*cmd)
{
	message_error(err, cmd);
	message_error2(err, cmd);
	message_error3(err, cmd);
}
