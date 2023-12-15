/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 10:10:59 by niboukha          #+#    #+#             */
/*   Updated: 2023/08/08 15:20:02 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_minishell	*minishell;
	char		*str;
	char		*s;

	(void)av;
	init_struct(ac, env);
	hide_ctrl();
	while (1)
	{
		g_data->is_child = 0;
		g_data->hdoc = 0;
		g_data->flg = 0;
		signal(SIGINT, sig_in_process);
		signal(SIGQUIT, SIG_IGN);
		dup2(g_data->std_in, STDIN_FILENO);
		dup2(g_data->std_out, STDOUT_FILENO);
		str = readline("MINISHELL> ");
		if (!check_input(str, &s))
			return (0);
		minishell = parser(s);
		free(s);
		execution(minishell);
		ft_clear_list_commands(&minishell);
	}
	return (0);
}
