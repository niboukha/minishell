/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:18:35 by shicham           #+#    #+#             */
/*   Updated: 2023/08/08 15:20:59 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	find_var(t_data *data)
{
	if (ft_isdigit(data->content[*(data->i)]) && (*data->i)++)
		return ;
	while (data->content[*(data->i)]
		&& !ft_strchr(" ><|\"\'\n\r\v\f\t", data->content[*(data->i)]))
	{
		if (data->content[*(data->i)] && data->content[*(data->i)] == '_')
			(*data->i)++;
		else if (!ft_isalnum(data->content[*(data->i)]))
			break ;
		else
			(*data->i)++;
	}
}

char	*ft_expand(t_data *data)
{
	char			*var;
	char			*res;
	unsigned int	start;
	size_t			end;
	int				save_exit;

	res = NULL;
	start = ++(*data->i);
	if (data->content[*(data->i)] == '?' && (*data->i)++)
	{
		save_exit = g_data->exit_code;
		if (g_data->flg == 1)
			g_data->exit_code = 0;
		return (ft_itoa(save_exit));
	}
	find_var(data);
	end = (*data->i);
	var = ft_substr(data->content, start, end - start);
	res = ft_strdup(find_key_env(var));
	toggle_char(res);
	free(var);
	return (res);
}
