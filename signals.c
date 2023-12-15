/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 22:55:05 by niboukha          #+#    #+#             */
/*   Updated: 2023/08/08 10:47:22 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	sig_in_process(int signum)
{
	if (signum == SIGINT && !g_data->is_child)
	{
		g_data->exit_code = 1;
		ft_putendl_fd("", 1);
		rl_replace_line("", STDERR_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_in_child(int signum)
{
	if (signum == SIGINT && g_data->is_child == 1)
		g_data->exit_code = VAL_SIGINT;
	if (signum == SIGQUIT)
		g_data->exit_code = VAL_SIGQUIT;
}

void	hide_ctrl(void)
{
	struct termios	attributes;

	if (tcgetattr(STDIN_FILENO, &attributes) == -1)
		perror("minishell ");
	attributes.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &attributes) == -1)
		perror("minishell ");
}

void	sig_in_heredoc(int signum)
{
	if (signum == SIGINT && !g_data->hdoc)
	{
		g_data->exit_code = 1;
		g_data->hdoc = 1;
		ft_putstr_fd("\n", STDERR_FILENO);
		close(0);
	}
}
