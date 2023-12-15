/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:28:03 by shicham           #+#    #+#             */
/*   Updated: 2023/08/08 15:12:12 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expand_inside_here_doc(char *str)
{
	int				i;
	unsigned int	start;
	size_t			end;
	char			*res;
	t_data			data;

	i = -1;
	res = NULL;
	start = 0;
	data.content = str;
	data.i = &i;
	while (str[++i])
	{
		if (str[i] == '$' && !ft_strchr(" \"\n\r\v\f\t", str[i + 1]))
		{
			end = i;
			res = ft_join(res, ft_substr(str, start, end - start));
			res = ft_join(res, ft_expand(&data));
			start = i;
			(!ft_isalnum(str[i])) && (i--);
		}
	}
	res = ft_join(res, ft_substr(str, start, i - start));
	free(str);
	return (res);
}

int	read_here_doc(char *path_file, char *delim, int flag)
{
	int		fd;
	char	*input;

	signal(SIGINT, sig_in_heredoc);
	unlink(path_file);
	fd = open(path_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		input = readline("> ");
		if (!input || !ft_strcmp(input, delim))
		{
			g_data->exit_code = 0;
			free(delim);
			free(input);
			break ;
		}
		input = ft_join(input, ft_strdup("\n"));
		if (flag)
			input = expand_inside_here_doc(input);
		write(fd, input, ft_strlen(input));
		free(input);
	}
	close(fd);
	return (fd);
}

void	check_nbr_here_docs(t_minishell *head)
{
	t_minishell	*ptr_cmd;
	t_files		*head_redi;
	int			here_docs;

	here_docs = 0;
	ptr_cmd = head;
	while (ptr_cmd)
	{
		head_redi = ptr_cmd->redir;
		while (head_redi)
		{
			if (head_redi->type == HERE_DOC)
				here_docs++;
			head_redi = head_redi->next;
		}
		ptr_cmd = ptr_cmd->next;
	}
	if (here_docs > 16)
	{
		write(2, "minishell: maximum here-document count exceeded \n", 50);
		exit_with_status(2);
		exit(g_data->exit_code);
	}
}

void	create_name(t_files *redi, int here_docs)
{
	char	*here_doc;

	here_doc = ft_join(ft_strdup("/tmp/here_doc_"),
			ft_substr(ttyname(STDIN_FILENO), 5, 7));
	here_doc = ft_join(here_doc, ft_itoa(here_docs));
	redi->fd = read_here_doc(here_doc, redi->file, redi->flag);
	redi->file = here_doc;
	redi->type = IN;
}

bool	open_here_docs(t_minishell *head)
{
	t_files		*redi;
	t_minishell	*ptr_cmd;
	int			here_docs;

	check_nbr_here_docs(head);
	here_docs = 0;
	ptr_cmd = head;
	while (ptr_cmd)
	{
		redi = ptr_cmd->redir;
		while (redi)
		{
			if (g_data->hdoc == 1)
				return (0);
			if (redi->type == HERE_DOC)
			{
				create_name(redi, here_docs);
				here_docs++;
			}
			redi = redi->next;
		}
		ptr_cmd = ptr_cmd->next;
	}
	return (1);
}
