/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 19:32:01 by jawatter          #+#    #+#             */
/*   Updated: 2018/11/11 19:12:16 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t z;

	z = 0;
	while (z < n)
	{
		((char *)s1)[z] = ((char *)s2)[z];
		z++;
	}
	return (s1);
}
