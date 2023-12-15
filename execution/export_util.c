/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 21:03:27 by niboukha          #+#    #+#             */
/*   Updated: 2023/08/04 16:40:29 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*get_if_exist(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (new->key && !ft_strcmp(tmp->key, new->key))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	get_new_node(char *str, t_list *new)
{
	char	*s;

	s = ft_strchr(str, '=');
	if (!s)
	{
		new->op = 'c';
		new->key = ft_strdup(str);
		new->value = NULL;
	}
	else
	{
		new->value = ft_strdup(s + 1);
		if (*(s - 1) == '+')
		{
			new->op = '+';
			new->key = ft_substr(str, 0, s - 1 - str);
		}
		else
		{
			new->op = '=';
			new->key = ft_substr(str, 0, s - str);
		}
	}
}

t_list	*add_env(char *str)
{
	t_list	*new;

	new = malloc (sizeof(t_list));
	get_new_node(str, new);
	if (!ft_alphanum(new->key))
	{
		free(new->key);
		free(new->value);
		free(new);
		g_data->exit_code = 1;
		exit_code(EXPORT_ERR, new->key);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

void	lst_addexport(t_list **lst, t_list *new)
{
	t_list	*exist;

	if (!new)
		return ;
	exist = get_if_exist(lst, new);
	if (exist)
	{
		if (new->op == '=')
		{
			free(exist->value);
			exist->value = new->value;
		}
		if (new->op == '+')
			exist->value = ft_join(exist->value, new->value);
		free(new->key);
		free(new);
	}
	else
		add_sortedexport(lst, new);
}
