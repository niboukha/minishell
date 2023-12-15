/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:26:54 by shicham           #+#    #+#             */
/*   Updated: 2023/08/08 12:16:55 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_files(t_files *head_redi)
{
	if (head_redi->flag == -4)
	{
		ft_perror(-4, head_redi->file);
		return (-1);
	}
	if (head_redi->type == IN)
		head_redi->fd = open(head_redi->file, O_RDWR, 0644);
	else if (head_redi->type == TRUNC)
		head_redi->fd = open(head_redi->file,
				O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else if (head_redi->type == APPEND)
	{
		head_redi->fd = open(head_redi->file,
				O_CREAT | O_APPEND | O_WRONLY, 0644);
	}
	if (head_redi->fd < 0 && !g_data->hdoc)
	{
		ft_perror(errno, head_redi->file);
		return (-1);
	}
	return (head_redi->fd);
}

void	check_file_type(t_files *head_redi, t_minishell *ptr_cmd)
{
	if (head_redi->type == IN)
	{
		if (ptr_cmd->infile)
			close(ptr_cmd->infile);
		ptr_cmd->infile = open_files(head_redi);
	}
	else if (head_redi->type == TRUNC)
	{
		if (ptr_cmd->outfile != 1)
			close(ptr_cmd->outfile);
		ptr_cmd->outfile = open_files(head_redi);
	}
	else
	{
		if (ptr_cmd->outfile != 1)
			close(ptr_cmd->outfile);
		ptr_cmd->outfile = open_files(head_redi);
	}
}

void	open_files_and_here_docs(t_minishell *head)
{
	t_files		*head_redi;
	t_minishell	*ptr_cmd;

	if (!open_here_docs(head))
		return ;
	ptr_cmd = head;
	while (ptr_cmd)
	{
		head_redi = ptr_cmd->redir;
		ptr_cmd->infile = 0;
		ptr_cmd->outfile = 1;
		while (head_redi)
		{
			check_file_type(head_redi, ptr_cmd);
			if (ptr_cmd->outfile < 0 || ptr_cmd->infile < 0)
				break ;
			head_redi = head_redi->next;
		}
		ptr_cmd = ptr_cmd->next;
	}
}
