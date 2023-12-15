/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:30:40 by shicham           #+#    #+#             */
/*   Updated: 2023/08/03 15:23:44 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_whitespace(t_data *data)
{
	while (data->content[*(data->i)]
		&& ft_strchr(" \t\n\r\f\v", data->content[*(data->i)]))
		(*data->i)++;
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	count;

	count = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	if (start < ft_strlen(s))
	{
		while (count < len)
		{
			result[count] = s[start];
			count++;
			start++;
		}
	}
	result[count] = '\0';
	return (result);
}

char	*ft_join(char *s1, char *s2)
{
	char	*result;
	int		i;
	int		len_s1;

	if (!s1 && !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	result = malloc((len_s1 + ft_strlen(s2) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2 && s2[i])
	{
		result[len_s1 + i] = s2[i];
		i++;
	}
	result[len_s1 + i] = '\0';
	return (free(s1), free(s2), result);
}
