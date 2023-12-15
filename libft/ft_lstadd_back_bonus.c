/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:00:20 by niboukha          #+#    #+#             */
/*   Updated: 2023/08/03 14:46:44 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	add_sortedexport(t_list **lst, t_list *new)
{
	t_list	*tmp;
	t_list	*tp;

	if (!new)
		return ;
	tp = NULL;
	tmp = *lst;
	while (tmp && tmp->next && ft_strcmp(tmp->next->key, new->key) < 0)
		tmp = tmp->next;
	if (!tmp || ft_strcmp((*lst)->key, new->key) > 0)
		ft_lstadd_front(lst, new);
	else
	{
		tp = tmp->next;
		tmp->next = new;
		new->next = tp;
	}
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!new)
		return ;
	last = ft_lstlast(*lst);
	if (*lst == NULL)
		*lst = new;
	else
		last->next = new;
}
