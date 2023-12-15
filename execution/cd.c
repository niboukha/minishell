/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 22:36:04 by niboukha          #+#    #+#             */
/*   Updated: 2023/08/08 14:27:54 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*new_cmd_env(char *str)
{
	char	*path;

	if (!str)
	{
		path = find_key_env("HOME");
		if (!path)
		{
			g_data->exit_code = 1;
			exit_code(HOME_NOT_SET, NULL);
			return (NULL);
		}
	}
	else if (str[0] == '-')
	{
		path = find_key_env("OLDPWD");
		if (!path)
		{
			g_data->exit_code = 1;
			exit_code(OLDPWD_NOT_SET, NULL);
			return (NULL);
		}
	}
	else
		path = str;
	return (path);
}

void	set_val_key(char *key, char *value)
{
	t_list	*lst;

	lst = g_data->tenv;
	while (lst)
	{
		if (!ft_strcmp(lst->key, key))
		{
			if (lst->value)
				free(lst->value);
			lst->value = "";
			lst->value = ft_strjoin(lst->value, value);
		}
		lst = lst->next;
	}
}

char	*up_cwd(char *cwd)
{
	cwd = NULL;
	return (getcwd(cwd, sizeof(NULL)));
}

void	handel_path(t_minishell *minishell, int i)
{
	char	*cwd;
	char	*new_cwd;

	cwd = NULL;
	g_data->exit_code = 0;
	cwd = getcwd(cwd, sizeof(cwd));
	new_cwd = new_cmd_env(minishell->cmd[i]);
	if (!new_cwd)
		return ;
	if (new_cwd && chdir(new_cwd) == -1)
	{
		free(cwd);
		exit_code(CHDIR_ERR, new_cwd);
		return ;
	}
	set_val_key("OLDPWD", cwd);
	if (cwd)
		free (cwd);
	cwd = up_cwd(cwd);
	set_val_key("PWD", cwd);
	if (g_data->tmp_pwd)
		free(g_data->tmp_pwd);
	g_data->tmp_pwd = cwd;
	if (minishell->cmd[i] && !ft_strcmp(minishell->cmd[i], "-"))
		pwd(minishell);
}

void	cd(t_minishell *minishell)
{
	int		i;

	i = 0;
	while (++i <= minishell->len)
	{
		if (minishell->cmd[i])
		{
			handel_path(minishell, i);
			break ;
		}
		handel_path(minishell, i);
	}
}
