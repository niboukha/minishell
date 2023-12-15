/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:19:41 by shicham           #+#    #+#             */
/*   Updated: 2023/08/04 23:50:48 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*loop_until_delim(char *str, int *i, unsigned int *start, char delim)
{
	char	*res;
	size_t	end;

	*start = ++(*i);
	while (str[*i] && str[*i] != delim)
		(*i)++;
	end = *i;
	res = ft_substr(str, *start, end - (*start));
	*start = ++(*i);
	return (res);
}

char	*extract_string_within_quotes(char *str)
{
	int				i;
	unsigned int	start;
	size_t			end;
	char			*res;

	i = 0;
	start = 0;
	res = NULL;
	while (str && str[i])
	{
		if (str[i] == '\'')
			res = ft_join(res, loop_until_delim(str, &i, &start, str[i]));
		else if (str[i] == '\"')
			res = ft_join(res, loop_until_delim(str, &i, &start, str[i]));
		else
		{
			while (str[i] && str[i] != '\'' && str[i] != '\"')
				i++;
			end = i;
			res = ft_join(res, ft_substr(str, start, end - start));
		}
		if (!str[i])
			break ;
	}
	return (free(str), res);
}
