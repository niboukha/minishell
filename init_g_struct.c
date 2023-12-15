/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_g_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 14:40:15 by niboukha          #+#    #+#             */
/*   Updated: 2023/08/08 15:10:05 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init_struct(int ac, char **env)
{
	g_data = malloc (sizeof(t_global));
	g_data->tenv = save_env(env);
	g_data->exit_code = 0;
	g_data->flag = 0;
	g_data->tmp_pwd = NULL;
	g_data->std_in = dup(0);
	g_data->std_out = dup(1);
	g_data->hdoc = 0;
	g_data->is_child = 0;
	g_data->flg = 0;
	if (ac != 1)
	{
		exit_code (NUM_ARGS, 0);
		exit(EXIT_FAILURE);
	}
}

int	check_input(char *str, char **s)
{
	if (!str || *str)
	{
		if (!str)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			return (0);
		}
		add_history(str);
	}
	*s = ft_strtrim(str, " \t\n\v\r");
	free(str);
	return (1);
}
