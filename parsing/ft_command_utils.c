/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:20:23 by shicham           #+#    #+#             */
/*   Updated: 2023/08/08 14:26:08 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_minishell	*create_command_node(t_head *_head)
{
	t_minishell	*command;
	t_node		*tmp;
	int			lstsize;
	int			i;

	command = malloc(sizeof(t_minishell));
	lstsize = _ft_lst_size(_head->h_node);
	command->len = lstsize;
	command->cmd = malloc((lstsize + 1) * sizeof(char *));
	i = 0;
	tmp = _head->h_node;
	while (tmp)
	{
		if (tmp->str)
		{
			command->cmd[i] = ft_strdup(tmp->str);
			i++;
		}
		tmp = tmp->next;
	}
	command->cmd[i] = NULL;
	command->redir = _head->h_files;
	command->next = NULL;
	return (command);
}

void	ft_clear_list_commands(t_minishell **head)
{
	t_minishell	*tmp;
	int			i;

	if (!(*head))
		return ;
	tmp = *head;
	*head = (*head)->next;
	while (*head)
	{
		ft_clear_redir(&tmp->redir);
		i = -1;
		while (++i < tmp->len)
			free(tmp->cmd[i]);
		free(tmp->cmd);
		free(tmp);
		tmp = *head;
		*head = (*head)->next;
	}
	ft_clear_redir(&tmp->redir);
	i = -1;
	while (++i < tmp->len)
		free(tmp->cmd[i]);
	free(tmp->cmd);
	free(tmp);
}

t_minishell	*ft_last_command(t_minishell *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	ft_command_add_back(t_minishell **head, t_minishell *new)
{
	t_minishell	*command_node;

	if (*head)
	{
		command_node = ft_last_command(*head);
		command_node->next = new;
	}
	else
		*head = new;
}

int	ftlstsize(t_minishell *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
