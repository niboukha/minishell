/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:48:34 by niboukha          #+#    #+#             */
/*   Updated: 2023/08/08 11:17:18 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_options(t_minishell *minishell, int i)
{
	int	j;
	int	c;
	int	flag;

	c = 1;
	flag = 0;
	j = 0;
	if (minishell->cmd[i] && !minishell->cmd[i][j + 1])
		return (flag);
	while (minishell->cmd[i] && minishell->cmd[i][j])
	{
		if (minishell->cmd[i][j] == 'n')
			c++;
		j++;
	}
	if (c == j)
		flag++;
	return (flag);
}

void	write_echo(t_minishell *minishell, int i)
{
	int	c;

	c = 0;
	while (i < minishell->len)
	{
		if (minishell->cmd[i])
		{
			c++;
			if (c != 1)
				ft_putchar_fd(' ', minishell->outfile);
			ft_putstr_fd(minishell->cmd[i], minishell->outfile);
		}
		i++;
	}
}

void	echo(t_minishell *minishell)
{
	int	i;
	int	flag;
	int	b;

	i = 1;
	flag = 0;
	g_data->exit_code = 0;
	while (i < minishell->len)
	{
		while (i < minishell->len && !minishell->cmd[i])
			i++;
		if (minishell->cmd[i] && minishell->cmd[i][0] != '-')
			break ;
		b = check_options(minishell, i);
		flag += b;
		if (b == 1)
			i++;
		else
			break ;
	}
	write_echo(minishell, i);
	if (flag < 1)
		write(minishell->outfile, "\n", 1);
}
