/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_node_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:22:18 by shicham           #+#    #+#             */
/*   Updated: 2023/08/08 14:25:23 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	_ft_lst_size(t_node *lst)
{
	int	size_lst;

	size_lst = 0;
	while (lst)
	{
		if (lst->str)
			size_lst++;
		lst = lst->next;
	}
	return (size_lst);
}

void	_ft_lst_clear(t_node **lst, void (*del)(void *))
{
	t_node	*node;

	if (!*lst || !del)
		return ;
	node = *lst;
	*lst = (*lst)->next;
	while (*lst)
	{
		(*del)(node->str);
		free(node);
		node = *lst;
		*lst = (*lst)->next;
	}
	(*del)(node->str);
	free(node);
	*lst = NULL;
}

t_node	*_ft_lst_last(t_node *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_node	*_ft_lst_new(char *content)
{
	t_node	*lstnew;

	lstnew = malloc(sizeof(t_node));
	if (!lstnew)
		return (NULL);
	lstnew->str = content;
	lstnew->next = NULL;
	return (lstnew);
}

void	_ft_lst_add_back(t_node **lst, t_node *new)
{
	t_node	*node;

	if (*lst)
	{
		node = _ft_lst_last(*lst);
		node->next = new;
	}
	else
		*lst = new;
}
