/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:43:59 by niboukha          #+#    #+#             */
/*   Updated: 2023/08/08 15:19:16 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execution(t_minishell *minishell)
{
	if (!minishell)
	{
		if (g_data->flag)
			g_data->exit_code = 0;
		return ;
	}
	if (ftlstsize(minishell) > 1)
		g_data->flg = 1;
	if (ftlstsize(minishell) == 1
		&& is_builtins(minishell) == 1)
	{
		exec_builtins(minishell);
		return ;
	}
	if (!minishell->cmd)
		return ;
	exec_in_child(minishell);
}
