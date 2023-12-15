/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:28:33 by shicham           #+#    #+#             */
/*   Updated: 2023/08/08 11:06:17 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	init_parse(int *i, char *input, t_minishell **head, t_data *data)
{
	*i = 0;
	data->content = input;
	data->i = i;
	*head = NULL;
	if (!input[*i])
		return (g_data->flag = 1, 0);
	return (1);
}

t_minishell	*parser(char *input)
{
	t_data		data;
	t_minishell	*head;
	t_minishell	*new_node;
	t_head		*_head;
	int			i;

	if (!init_parse(&i, input, &head, &data))
		return (NULL);
	while (input[i])
	{
		g_data->flag = 0;
		if (input[0] == '|' && !syntax_error(&input[i]))
			return (NULL);
		_head = return_head(&data, input, &i, &head);
		if (!_head)
			return (NULL);
		new_node = create_command_node(_head);
		_ft_lst_clear(&_head->h_node, free);
		free(_head);
		ft_command_add_back(&head, new_node);
		if (!input[i])
			break ;
	}
	open_files_and_here_docs(head);
	return (head);
}
