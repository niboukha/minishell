/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 11:26:07 by niboukha          #+#    #+#             */
/*   Updated: 2023/08/03 11:00:00 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*valid_cmd(t_minishell *minishell)
{
	char	*cmd_tmp;
	int		i;

	i = 0;
	if (!minishell->cmd[0][0])
		return (NULL);
	if (ft_strchr(minishell->cmd[0], '/'))
		return (minishell->cmd[0]);
	if (!minishell->path)
		return (minishell->cmd[0]);
	while (minishell->path[i])
	{
		cmd_tmp = ft_strjoin(minishell->path[i], "/");
		cmd_tmp = ft_strjoin(cmd_tmp, minishell->cmd[0]);
		if (access(cmd_tmp, X_OK | F_OK) == 0)
			return (cmd_tmp);
		free(cmd_tmp);
		i++;
	}
	if (check_slash(minishell->cmd[0]) != 0)
		return (NULL);
	return (minishell->cmd[0]);
}
