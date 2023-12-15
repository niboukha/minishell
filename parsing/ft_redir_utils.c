/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:22:53 by shicham           #+#    #+#             */
/*   Updated: 2023/08/03 14:42:58 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_clear_redir(t_files **head)
{
	t_files	*ptr;

	if (!(*head))
		return ;
	ptr = *head;
	*head = (*head)->next;
	while (*head)
	{
		free(ptr->file);
		free(ptr);
		ptr = *head;
		*head = (*head)->next;
	}
	free(ptr->file);
	free(ptr);
	(*head) = NULL;
}

t_files	*ft_files_new(char *file, int type)
{
	t_files	*redir;

	if (!file)
		return (NULL);
	redir = malloc(sizeof(t_files));
	redir->file = file;
	redir->type = type;
	redir->next = NULL;
	return (redir);
}

t_files	*ft_last_files(t_files *redir)
{
	t_files	*ptr;

	if (!redir)
		return (NULL);
	ptr = redir;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

void	ft_add_back_redir(t_files **head, t_files *new)
{
	t_files	*ptr;

	if (*head)
	{
		ptr = ft_last_files(*head);
		ptr->next = new;
	}
	else
		*head = new;
}
