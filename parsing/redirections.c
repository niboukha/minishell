/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:29:33 by shicham           #+#    #+#             */
/*   Updated: 2023/08/08 12:58:08 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_ambiguous(char *str, char *save_str, int *flg_amb)
{
	int		i;
	char	**split_str;
	char	*res;

	if (!str)
	{
		*flg_amb = -4;
		return (save_str);
	}
	split_str = ft_split_(str);
	i = -1;
	while (split_str[++i])
		;
	if (i == 1)
	{
		res = extract_string_within_quotes(split_str[0]);
		return (free(split_str), free(save_str), free(str), _abs(res));
	}
	*flg_amb = -4;
	free(str);
	i = -1;
	while (split_str[++i])
		free(split_str[i]);
	free(split_str);
	return (save_str);
}

char	*get_file_name(t_data *data, int *here_doc, int flag, int *amb_flg)
{
	char	*str;
	char	*save_str;
	int		i;

	i = (*data->i);
	save_str = collect_string(data, here_doc, 0);
	if (check_quotes(save_str))
	{
		g_data->exit_code = 258;
		return (free(save_str), NULL);
	}
	(*data->i) = i;
	str = collect_string(data, here_doc, flag);
	if (!here_doc)
		return (check_ambiguous(str, save_str, amb_flg));
	free(save_str);
	str = extract_string_within_quotes(str);
	return (_abs(str));
}

t_files	*create_redi(t_data *data, int skip, int type)
{
	t_files	*redi;
	int		here_doc;
	int		flg_amb;

	flg_amb = -10;
	here_doc = 1;
	(*data->i) += skip;
	if ((type == TRUNC || type == APPEND) && data->content[*(data->i)] == '|')
		(*data->i)++;
	skip_whitespace(data);
	if (!syntax_error(&data->content[*(data->i)]))
		return (NULL);
	if (type == HERE_DOC)
		redi = ft_files_new(get_file_name(data, &here_doc, 0, NULL), type);
	else
		redi = ft_files_new(get_file_name(data, NULL, 1, &flg_amb), type);
	if (redi && type == HERE_DOC)
		redi->flag = here_doc;
	else if (redi)
		redi->flag = flg_amb;
	return (redi);
}

t_files	*redirections(t_data *data)
{
	t_files	*redi;

	redi = NULL;
	if (data->content[*(data->i)] == '>'
		&& data->content[*(data->i) + 1] == '>')
		redi = create_redi(data, 2, APPEND);
	else if (data->content[*(data->i)] == '<'
		&& data->content[*(data->i) + 1] == '<')
		redi = create_redi(data, 2, HERE_DOC);
	else if (data->content[*(data->i)] == '>')
		redi = create_redi(data, 1, TRUNC);
	else if (data->content[*(data->i)] == '<')
		redi = create_redi(data, 1, IN);
	return (redi);
}
