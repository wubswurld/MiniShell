/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 18:22:10 by jawatter          #+#    #+#             */
/*   Updated: 2018/11/15 18:29:44 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int		x;
	int		len;
	char	wubs;

	x = 0;
	len = ft_strlen(str);
	while (len - 1 > x)
	{
		wubs = str[x];
		str[x] = str[len - 1];
		str[len - 1] = wubs;
		len--;
		x++;
	}
	return (str);
}
