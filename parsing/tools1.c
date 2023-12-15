/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:33:40 by shicham           #+#    #+#             */
/*   Updated: 2023/08/07 18:58:33 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*_abs(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
	{
		if (str[i] < 0)
			str[i] = str[i] * (-1);
	}
	return (str);
}

void	toggle_char(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			str[i] = str[i] * (-1);
		i++;
	}
}

void	exit_with_status(int exit_status)
{
	g_data->exit_code = exit_status;
}

short	ft_perror(int err, char *reas)
{
	if (err == -4)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(reas, STDERR_FILENO);
		ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
		return (1);
	}
	if (err > 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(reas, STDERR_FILENO);
		ft_putstr_fd(" :", STDERR_FILENO);
		ft_putendl_fd(strerror(err), STDERR_FILENO);
		return (1);
	}
	return (1);
}
