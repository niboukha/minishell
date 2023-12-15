/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:50:24 by niboukha          #+#    #+#             */
/*   Updated: 2023/08/04 23:32:56 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_export(t_minishell *minishell)
{
	t_list	*tmp;

	tmp = g_data->tenv;
	while (tmp)
	{
		if (!tmp->key)
			return ;
		ft_putstr_fd("declare -x ", minishell->outfile);
		ft_putstr_fd(tmp->key, minishell->outfile);
		if (tmp->value)
		{
			ft_putstr_fd("=\"", minishell->outfile);
			ft_putstr_fd(tmp->value, minishell->outfile);
			ft_putstr_fd("\"", minishell->outfile);
		}
		write(minishell->outfile, "\n", 1);
		tmp = tmp->next;
	}
}

void	export(t_minishell *minishell)
{
	int	i;
	int	flag;

	g_data->exit_code = 0;
	flag = 0;
	i = 0;
	while (++i < minishell->len)
	{
		if (minishell->cmd[i] && minishell->cmd[i][0] != '_'
			&& !ft_isalpha(minishell->cmd[i][0]))
		{
			flag = 1;
			g_data->exit_code = 1;
			exit_code(EXPORT_ERR, minishell->cmd[i]);
			continue ;
		}
		if (minishell->cmd[i])
		{
			lst_addexport(&g_data->tenv, add_env(minishell->cmd[i]));
			flag = 1;
		}
	}
	if (!flag)
		print_export(minishell);
}
