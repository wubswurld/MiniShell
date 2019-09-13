/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 00:32:11 by jawatter          #+#    #+#             */
/*   Updated: 2018/11/15 17:27:36 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int nbr)
{
	char	*str;
	int		neg;
	int		x;

	x = ft_nbr_len(nbr);
	neg = 0;
	if (nbr == -2147483648)
		return (str = ft_strdup("-2147483648"));
	if (!(str = ft_strnew(x + 1)))
		return (NULL);
	if (nbr < 0)
	{
		neg = 1;
		str[0] = '-';
		nbr *= -1;
	}
	while (x >= neg)
	{
		str[x] = (nbr % 10) + 48;
		nbr /= 10;
		x--;
	}
	str[ft_strlen(str)] = '\0';
	return (str);
}
