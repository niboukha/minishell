/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:56:50 by niboukha          #+#    #+#             */
/*   Updated: 2023/08/08 09:31:38 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_err(char	*str)
{
	g_data->exit_code = 255;
	exit_code(EXIT_N_A_R, str);
}

int	ft_atoi_exit(char *str)
{
	int					i;
	int					signe;
	unsigned long long	result;

	i = 0;
	signe = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] <= 13 && str[i] >= 9))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			signe *= -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = str[i++] + result * 10 - '0';
		if (result > 9223372036854775807 && signe == 1)
			return (print_err(str), 255);
		if (result > 9223372036854775808UL && signe == -1)
			return (print_err(str), 255);
	}
	if (str[i])
		return (print_err(str), 255);
	return (signe * result);
}

bool	check_exit(t_minishell *minishell, int i, int *nb, int *c)
{
	if (minishell->cmd[i])
	{
		(*c)++;
		if (*c == 2)
		{
			g_data->exit_code = 1;
			exit_code(EXIT_A_ERR, NULL);
			return (1);
		}
		*nb = ft_atoi_exit(minishell->cmd[i]);
		if (*nb == 255)
			exit(*nb);
	}
	return (0);
}

void	f_exit(t_minishell *minishell)
{
	int				i;
	int				nb;
	unsigned char	exit_nb;
	int				c;

	i = 1;
	nb = 0;
	c = 0;
	ft_putstr_fd("exit\n", 1);
	if (!minishell->cmd[i] && minishell->len == 1)
		exit (g_data->exit_code);
	while (i < minishell->len)
	{
		if (check_exit(minishell, i, &nb, &c))
			return ;
		i++;
	}
	exit_nb = (unsigned char)nb;
	g_data->exit_code = exit_nb;
	exit (exit_nb);
}
