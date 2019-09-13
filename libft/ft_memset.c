/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 17:32:40 by jawatter          #+#    #+#             */
/*   Updated: 2018/11/11 02:39:02 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *a, int b, size_t n)
{
	size_t x;

	x = 0;
	b = ((unsigned char)b);
	while (x < n)
	{
		((unsigned char *)a)[x] = ((unsigned char)b);
		x++;
	}
	return (a);
}
