/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niboukha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 10:08:10 by niboukha          #+#    #+#             */
/*   Updated: 2022/10/29 16:46:35 by niboukha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len_nbr(int nb)
{
	int	i;

	i = 0;
	if (nb <= 0)
	{
		i++;
		nb *= -1;
	}
	while (nb != 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	nb;
	char	*str;
	int		len;

	nb = n;
	len = len_nbr(n);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	len--;
	if (nb == 0)
		str[0] = 48;
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	while (nb != 0)
	{
		str[len] = 48 + (nb % 10);
		nb /= 10;
		len--;
	}
	return (str);
}
