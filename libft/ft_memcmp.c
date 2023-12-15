/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 21:22:32 by niboukha          #+#    #+#             */
/*   Updated: 2022/10/29 16:58:58 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*m;
	unsigned char	*m1;
	size_t			i;

	m = (unsigned char *)s1;
	m1 = (unsigned char *)s2;
	i = 0;
	while (i < n && (m[i] == m1[i]))
		i++;
	if (i < n)
		return (m[i] - m1[i]);
	else
		return (0);
}
