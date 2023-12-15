/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 11:47:09 by niboukha          #+#    #+#             */
/*   Updated: 2023/08/07 20:36:41 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	s_first(char const *str, char const *set)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(set, str[i]))
			i++;
		else
			break ;
	}
	return (i);
}

static int	s_last(char const *str, char const *set)
{
	size_t	len;

	len = ft_strlen(str);
	while (len)
	{
		if (ft_strchr(set, str[len]))
			len--;
		else
			break ;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	first;
	size_t	last;
	size_t	i;

	if (!s1 || !set)
		return (ft_strdup(""));
	i = 0;
	first = s_first(s1, set);
	last = s_last(s1, set);
	if (first > last)
		return (ft_strdup(""));
	str = malloc(last - first + 2);
	if (!str)
		return (0);
	while (i < (last - first + 1))
	{
		str[i] = s1[first + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
