/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 09:57:15 by shicham           #+#    #+#             */
/*   Updated: 2023/08/03 22:51:08 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*collect_double_quotes(t_data *data, int flag)
{
	unsigned int	start;
	size_t			end;
	char			*res;

	start = (*data->i)++;
	res = NULL;
	while (data->content[*(data->i)] && data->content[*(data->i)] != '\"')
	{
		if (flag && data->content[*(data->i)] == '$'
			&& !ft_strchr(" \"\n\r\v\f\t", data->content[*(data->i) + 1]))
		{
			end = (*data->i);
			res = ft_join(res, ft_substr(data->content, start, end - start));
			res = ft_join(res, ft_expand(data));
			start = (*data->i);
			if (!ft_isalnum(data->content[*(data->i)]))
				(*data->i)--;
		}
		(*data->i)++;
	}
	end = *(data->i);
	res = ft_join(res, ft_substr(data->content, start, end - start + 1));
	if (data->content[*(data->i)] == '\"')
		(*data->i)++;
	return (res);
}

char	*collect_single_quotes(t_data *data)
{
	unsigned int	start;
	size_t			end;
	char			*res;

	start = (*data->i)++;
	res = NULL;
	while (data->content[*(data->i)]
		&& data->content[*(data->i)] != '\'')
		(*data->i)++;
	end = *(data->i);
	res = ft_join(res, ft_substr(data->content, start, end - start + 1));
	if (data->content[*(data->i)] == '\'')
		(*data->i)++;
	return (res);
}

char	*collect_string_within_quotes(t_data *data, int flag)
{
	unsigned int	st;
	size_t			end;
	char			*res;

	st = (*data->i);
	res = NULL;
	while (data->content[*(data->i)]
		&& !ft_strchr(" ><|\"\'\n\r\v\f\t", data->content[*(data->i)]))
	{
		if (data->content[*(data->i)] == '$' && flag
			&& !ft_strchr(" ><|\"\'\n\r\v\f\t", data->content[*(data->i) + 1]))
		{
			end = (*data->i);
			if (data->content[st] != '$')
				res = ft_join(res, ft_substr(data->content, st, end - st));
			res = ft_join(res, ft_expand(data));
			if (ft_strchr("><| \n\r\v\f\t", data->content[*(data->i)]))
				return (res);
			st = (*data->i);
			(!ft_isalnum(data->content[*(data->i)]) && (*data->i)--);
		}
		(*data->i)++;
	}
	res = ft_join(res, ft_substr(data->content, st, *(data->i) - st));
	return (res);
}

char	*collect_string(t_data *data, int *here_doc, int flag)
{
	char	*res;

	res = NULL;
	while (data->content[*(data->i)]
		&& !ft_strchr(" ><|\n\r\v\f\t", data->content[*(data->i)]))
	{
		if (data->content[*(data->i)] == '\"')
		{
			if (here_doc)
				*here_doc = 0;
			res = ft_join(res, collect_double_quotes(data, flag));
		}
		else if (data->content[*(data->i)] == '\'')
		{
			if (here_doc)
				*here_doc = 0;
			res = ft_join(res, collect_single_quotes(data));
		}
		else if (!ft_strchr(" ><|\n\r\v\f\t", data->content[*(data->i)]))
			res = ft_join(res, collect_string_within_quotes(data, flag));
	}
	return (res);
}
