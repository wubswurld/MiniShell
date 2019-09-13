/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:43:46 by jawatter          #+#    #+#             */
/*   Updated: 2018/11/14 14:59:39 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	size_t x;

	x = 0;
	while (x < n)
	{
		if (((unsigned char *)s2)[x] == (unsigned char)c)
		{
			((unsigned char *)s1)[x] = ((unsigned char *)s2)[x];
			return (s1 + x + 1);
		}
		((unsigned char *)s1)[x] = ((unsigned char *)s2)[x];
		x++;
	}
	return (NULL);
}
