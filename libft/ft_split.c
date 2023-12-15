/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 00:43:39 by niboukha          #+#    #+#             */
/*   Updated: 2023/07/25 16:20:07 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	c_w(char const *str, char *c)
{
	int	w;

	if (!str)
		return (0);
	w = 0;
	if (!check_sep(*str, c) && *str)
	{
		w++;
		str++;
	}
	while (*str)
	{
		while (check_sep(*str, c))
		{
			str++;
			if (*str && !check_sep(*str, c))
				w++;
		}
		if (*str)
			str++;
	}
	return (w);
}

static int	len_w(char const *str, char *c)
{
	int	len;

	len = 0;
	while (*str && !check_sep(*str, c))
	{
		len++;
		str++;
	}
	return (len);
}

static void	ft_free(char **tab, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(tab[j]);
		j++;
	}
	free(tab);
}

char const	*skeep_separator(char const *s, char *c)
{
	while (check_sep(*s, c))
			s++;
	return (s);
}

char	**ft_split(char const *s, char *c)
{
	char	**tab;
	int		i;
	int		j;

	tab = ft_calloc(c_w(s, c) + 1, sizeof(char *));
	if (!tab || !s)
		return (NULL);
	i = -1;
	while (*s)
	{
		s = skeep_separator(s, c);
		if (!check_sep(*s, c) && *s)
		{
			j = 0;
			tab[++i] = (char *)ft_calloc(len_w(s, c) + 2, 1);
			if (!tab[i])
			{
				ft_free(tab, i);
				return (0);
			}
			while (*s && !check_sep(*s, c))
				tab[i][j++] = *s++;
		}
	}
	return (tab);
}
