/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:30:01 by shicham           #+#    #+#             */
/*   Updated: 2023/08/05 21:13:36 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_quotes(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (!str[i])
				return (write(2, "minishell: ': unclosed quotes\n", 31));
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			if (!str[i])
				return (write(2, "minishell: \": unclosed quotes\n", 31));
		}
		i++;
	}
	return (0);
}

bool	check_syntax_error(char *next)
{
	if (!*next || *next == '>' || *next == '<' || *next == '|')
		return (0);
	return (1);
}

void	print_error(char *next, int flag)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(UNEXPECTED_TOKEN, 2);
	ft_putstr_fd(" ", 2);
	if (!flag)
		ft_putstr_fd("`newline'\n", 2);
	else if (flag < 0)
	{
		ft_putchar_fd('`', 2);
		ft_putchar_fd(*next, 2);
		ft_putchar_fd(*(next + 1), 2);
		ft_putstr_fd("\'\n", 2);
	}
	else
	{
		ft_putchar_fd('`', 2);
		ft_putchar_fd(*next, 2);
		ft_putstr_fd("\'\n", 2);
	}
}

bool	syntax_error2(char *next)
{
	if (!*next)
	{
		print_error(NULL, 0);
		return (0);
	}
	else if (*next == '|')
	{
		print_error(next, 1);
		return (0);
	}
	return (1);
}

bool	syntax_error(char *next)
{
	if (check_syntax_error(next))
		return (1);
	else if (!(*next))
	{
		print_error(next, 0);
		exit_with_status(258);
	}
	else if ((*next))
	{
		if (!check_syntax_error(next + 1))
		{
			print_error(next, -1);
			exit_with_status(258);
			return (0);
		}
		print_error(next, 1);
		exit_with_status(258);
	}
	return (0);
}
