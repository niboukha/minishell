/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:36:46 by niboukha          #+#    #+#             */
/*   Updated: 2023/08/02 13:42:20 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(t_minishell *minishell)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, sizeof(cwd));
	if (!cwd)
		cwd = g_data->tmp_pwd;
	ft_putendl_fd(cwd, minishell->outfile);
	if (cwd != g_data->tmp_pwd)
		free(cwd);
}
