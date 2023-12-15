/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:22:06 by niboukha          #+#    #+#             */
/*   Updated: 2023/08/03 11:00:42 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*get_new_envv(char *env)
{
	t_list	*tenv;
	int		i;

	tenv = malloc (sizeof(t_list));
	i = 0;
	while (env[i] != '=')
		i++;
	tenv->key = ft_substr(env, 0, i);
	tenv->value = ft_substr(env, i + 1, ft_strlen(env));
	tenv->next = NULL;
	return (tenv);
}

t_list	*save_env(char **env)
{
	t_list	*lst;
	char	*tmp;
	int		i;

	lst = NULL;
	i = 0;
	while (env[i])
	{
		tmp = ft_strdup(env[i]);
		add_sortedexport(&lst, get_new_envv(tmp));
		free(tmp);
		i++;
	}
	return (lst);
}
