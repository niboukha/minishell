/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:05:34 by niboukha          #+#    #+#             */
/*   Updated: 2022/10/28 17:01:38 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	mult;
	size_t	i;

	i = 0;
	if (size && count > SIZE_MAX / size)
		return (NULL);
	mult = count * size;
	ptr = malloc(mult);
	if (!ptr)
		return (0);
	ft_bzero(ptr, mult);
	return (ptr);
}
