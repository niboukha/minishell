/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:25:45 by shicham           #+#    #+#             */
/*   Updated: 2023/08/04 23:51:19 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_words(char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		(str[i]) && (++count);
		while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		{
			if (str[i] == '\'')
				while (str[++i] && str[i] != '\'')
					;
			else if (str[i] == '\"')
				while (str[++i] && str[i] != '\"')
					;
			if (str[i])
				i++;
		}
		if (!str[i])
			break ;
	}
	return (count);
}

char	*get_word(char *str, int *i)
{
	unsigned int	start;
	size_t			end;

	start = *i;
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t' && str[*i] != '\n')
	{
		if (str[*i] == '\'')
			while (str[(*i)++] && str[*i] != '\'')
				;
		else if (str[*i] == '\"')
			while (str[(*i)++] && str[*i] != '\"')
				;
		if (!str[*i])
			break ;
		(*i)++;
	}
	end = *i;
	return (ft_substr(str, start, end - start));
}

char	**ft_split_(char *str)
{
	int		count;
	char	**res;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	count = count_words(str);
	res = malloc((count + 1) * sizeof(char *));
	i = -1;
	j = -1;
	while (str[++i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
			i++;
		if (count--)
			res[++j] = get_word(str, &i);
		if (!str[i])
			break ;
	}
	res[++j] = NULL;
	return (res);
}
