/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 09:40:39 by niboukha          #+#    #+#             */
/*   Updated: 2023/08/04 17:04:44 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	delete_node(char *str, t_list **env)
{
	t_list	*del;
	t_list	*prev;

	if (str && !ft_strcmp((*env)->key, str))
	{
		del = *env;
		*env = (*env)->next;
		ft_lstdelone(del, free);
		g_data->tenv = *env;
		return ;
	}
	del = *env;
	while (str && del->next)
	{
		prev = del;
		if (!ft_strcmp(str, del->next->key))
		{
			del = del->next;
			prev->next = del->next;
			ft_lstdelone(del, free);
			break ;
		}
		del = del->next;
	}
}

void	unset(t_minishell *minishell)
{
	int		i;
	t_list	*env;

	i = 1;
	while (i < minishell->len)
	{
		env = g_data->tenv;
		if (!env)
			return ;
		if (minishell->cmd[i] && !ft_alphanum(minishell->cmd[i]))
		{
			g_data->exit_code = 1;
			exit_code(UNSET_ERR, minishell->cmd[i]);
			i++;
			continue ;
		}
		delete_node(minishell->cmd[i], &env);
		g_data->tenv = env;
		i++;
	}
}
