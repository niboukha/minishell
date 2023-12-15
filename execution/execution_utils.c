/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:53:46 by niboukha          #+#    #+#             */
/*   Updated: 2023/08/07 21:25:31 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**check_path(void)
{
	t_list	*tmp;

	tmp = g_data->tenv;
	while (tmp)
	{
		if (ft_strcmp("PATH", tmp->key) == 0)
			return (ft_split(tmp->value, ":"));
		tmp = tmp->next;
	}
	return (NULL);
}

void	wait_child(t_minishell *minishell)
{
	int	status;
	int	i;

	i = 0;
	waitpid(minishell->pid, &status, 0);
	g_data->exit_code = WEXITSTATUS(status);
	if (g_data->hdoc)
		g_data->exit_code = 1;
	if (status == 2)
	{
		g_data->exit_code = VAL_SIGINT;
		ft_putendl_fd("^C", STDERR_FILENO);
	}
	if (status == 3)
	{
		g_data->exit_code = VAL_SIGQUIT;
		ft_putendl_fd("Quit: 3", STDERR_FILENO);
	}
	else if (WIFSIGNALED(status))
		g_data->exit_code = WTERMSIG(status) + 128;
	while (wait(NULL) != -1)
		;
}

void	free_path(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->path && minishell->path[i])
	{
		free(minishell->path[i]);
		i++;
	}
	free(minishell->path);
	minishell->path = NULL;
}

int	check_slash(char *path)
{
	int	i;

	i = -1;
	if (!path)
		return (0);
	while (path[++i])
	{
		if (path[i] == '/')
			return (1);
	}
	return (0);
}
