/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 22:04:49 by niboukha          #+#    #+#             */
/*   Updated: 2023/08/04 15:28:08 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtins(t_minishell *minishell)
{
	if (minishell->cmd[0] && (!ft_strcmp(minishell->cmd[0], "echo")
			|| !ft_strcmp(minishell->cmd[0], "cd")
			|| !ft_strcmp(minishell->cmd[0], "export")
			|| !ft_strcmp(minishell->cmd[0], "env")
			|| !ft_strcmp(minishell->cmd[0], "exit")
			|| !ft_strcmp(minishell->cmd[0], "pwd")
			|| !ft_strcmp(minishell->cmd[0], "unset")))
		return (1);
	return (0);
}

int	exec_builtins(t_minishell *minishell)
{
	if (!ft_strcmp(minishell->cmd[0], "echo"))
		echo(minishell);
	else if (!ft_strcmp(minishell->cmd[0], "cd"))
		cd(minishell);
	else if (!ft_strcmp(minishell->cmd[0], "export"))
		export(minishell);
	else if (!ft_strcmp(minishell->cmd[0], "env"))
		b_env(minishell);
	else if (!ft_strcmp(minishell->cmd[0], "exit"))
		f_exit(minishell);
	else if (!ft_strcmp(minishell->cmd[0], "unset"))
		unset(minishell);
	else if (!ft_strcmp(minishell->cmd[0], "pwd"))
		pwd(minishell);
	return (g_data->exit_code);
}
