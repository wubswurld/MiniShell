/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 23:07:52 by jawatter          #+#    #+#             */
/*   Updated: 2018/11/12 14:36:43 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s1, int c, size_t n)
{
	while (n--)
	{
		if (*(unsigned char *)s1 == (unsigned char)c)
			return ((unsigned char *)s1);
		s1++;
	}
	return (NULL);
}
