/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmalloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 17:23:31 by jawatter          #+#    #+#             */
/*   Updated: 2018/11/11 03:15:10 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t n)
{
	void	*tmp;

	tmp = (void *)malloc(n);
	if (tmp == NULL)
		return (NULL);
	ft_memset(tmp, 0, n);
	return (tmp);
}
