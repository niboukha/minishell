/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:20:03 by niboukha          #+#    #+#             */
/*   Updated: 2023/08/08 11:16:29 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*lst_new_back(t_node *head, char *str)
{
	t_node	*list;

	str = extract_string_within_quotes(str);
	list = _ft_lst_new(_abs(str));
	_ft_lst_add_back(&head, list);
	return (head);
}

int	norm(t_data *data, char **str)
{
	char	*save_str;
	int		i;

	i = (*data->i);
	save_str = collect_string(data, NULL, 0);
	if (check_quotes(save_str))
	{
		g_data->exit_code = 258;
		return (free(save_str), 0);
	}
	free(save_str);
	(*data->i) = i;
	*str = collect_string(data, NULL, 1);
	return (1);
}

t_node	*collect_node(t_data *data)
{
	t_node	*list;
	t_node	*head;
	char	*str;
	char	**split_str;
	int		i;

	list = NULL;
	head = NULL;
	str = NULL;
	if (!norm(data, &str))
		return (NULL);
	i = -1;
	split_str = ft_split_(str);
	if (!split_str || !split_str[0])
		return (lst_new_back(head, str));
	free(str);
	while (split_str && split_str[++i])
	{
		str = extract_string_within_quotes(split_str[i]);
		list = _ft_lst_new(_abs(str));
		_ft_lst_add_back(&head, list);
	}
	free(split_str);
	return (head);
}

bool	return_head_2(t_data *data, t_minishell **head,
		t_node **head_list, t_files **head_redi)
{
	t_files		*redi;
	t_node		*list;

	if (data->content[*(data->i)] == '>' || data->content[*(data->i)] == '<')
	{
		redi = redirections(data);
		if (!redi)
			return (ft_clear_redir(head_redi), _ft_lst_clear(head_list, free),
				ft_clear_list_commands(head), 0);
		ft_add_back_redir(head_redi, redi);
	}
	else if (!ft_strchr("><| \n\r\v\f\t", data->content[*(data->i)]))
	{
		list = collect_node(data);
		if (!list)
			return (ft_clear_redir(head_redi), _ft_lst_clear(head_list, free),
				ft_clear_list_commands(head), 0);
		_ft_lst_add_back(head_list, list);
	}
	return (1);
}

t_head	*return_head(t_data *data, char *input, int *i, t_minishell **head)
{
	t_node		*head_list;
	t_files		*head_redi;
	t_head		*_head;

	head_redi = NULL;
	head_list = NULL;
	_head = malloc(sizeof(t_head));
	while (input[*i] && input[*i] != '|')
	{
		skip_whitespace(data);
		if (!return_head_2(data, head, &head_list, &head_redi))
			return (free(_head), NULL);
	}
	if (input[*i] == '|')
	{
		(*i)++;
		skip_whitespace(data);
		if (!syntax_error2(&input[*i]))
			return (free(_head), ft_clear_redir(&head_redi),
				_ft_lst_clear(&head_list, free),
				ft_clear_list_commands(head), NULL);
	}
	_head->h_files = head_redi;
	_head->h_node = head_list;
	return (_head);
}
