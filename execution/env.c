/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 19:50:51 by niboukha          #+#    #+#             */
/*   Updated: 2023/08/02 13:43:26 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_env(void)
{
	t_list	*tmp;

	tmp = g_data->tenv;
	while (tmp)
	{
		if (tmp->value)
		{
			ft_putstr_fd(tmp->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(tmp->value, 1);
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
}

void	b_env(t_minishell *minishell)
{
	g_data->exit_code = 0;
	if (!minishell->cmd[1])
		print_env();
	else
	{
		g_data->exit_code = 127;
		exit_code(ENV_ERR, minishell->cmd[1]);
	}
}
