/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:13:51 by jawatter          #+#    #+#             */
/*   Updated: 2018/11/11 03:13:27 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	x;

	x = 0;
	if (!n)
		return (0);
	while (s1[x] && s2[x] && s1[x] == s2[x] && x < n - 1)
		x++;
	return (((unsigned char *)s1)[x] - ((unsigned char *)s2)[x]);
}
