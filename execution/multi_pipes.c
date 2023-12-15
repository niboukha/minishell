/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:56:16 by niboukha          #+#    #+#             */
/*   Updated: 2023/08/07 20:40:17 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_pipe(t_minishell *minishell)
{
	close(minishell->fd[0]);
	close(minishell->fd[1]);
}

void	dup_outfile_pipe(t_minishell *minishell)
{
	if (minishell->next)
	{
		if (minishell->outfile > 1)
		{
			dup2(minishell->outfile, 1);
			close(minishell->outfile);
		}
		else
		{
			dup2(minishell->fd[1], 1);
			close_pipe(minishell);
		}
	}
	else if (minishell->outfile > 1)
	{
		dup2(minishell->outfile, 1);
		close(minishell->outfile);
	}
	if (is_builtins(minishell) == 1)
	{
		g_data->exit_code = exec_builtins(minishell);
		exit(g_data->exit_code);
	}
}

bool	exec_child(t_minishell *minishell)
{
	if (pipe(minishell->fd) == -1)
		exit_code(PIPE_ERR, NULL);
	if (minishell->infile > 0)
	{
		dup2(minishell->infile, 0);
		close(minishell->infile);
	}
	minishell->pid = fork();
	if (minishell->pid == -1)
		return (exit_code(FORK_ERR, NULL), 0);
	g_data->is_child = 1;
	if (!minishell->pid)
	{
		signal(SIGINT, sig_in_child);
		signal(SIGQUIT, sig_in_child);
		if (minishell->infile == -1 || minishell->outfile == -1)
			exit(1);
		dup_outfile_pipe(minishell);
		execve_function(minishell);
	}
	dup2(minishell->fd[0], 0);
	close_pipe(minishell);
	return (1);
}

void	exec_in_child(t_minishell *minishell)
{
	t_minishell	*tmp;

	tmp = minishell;
	if (g_data->hdoc)
	{
		g_data->exit_code = 1;
		return ;
	}
	while (tmp)
	{
		if (tmp->cmd[0])
		{
			tmp->path = check_path();
			if (!exec_child(tmp))
				break ;
			if (minishell->outfile != 1)
				close(minishell->outfile);
			free_path(tmp);
			minishell->pid = tmp->pid;
		}
		tmp = tmp->next;
	}
	wait_child(minishell);
}
