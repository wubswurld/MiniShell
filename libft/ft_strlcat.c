/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:42:23 by jawatter          #+#    #+#             */
/*   Updated: 2018/11/11 18:48:17 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *s1, const char *s2, size_t n)
{
	size_t	a;
	int		j;
	int		x;

	a = 0;
	j = 0;
	x = ft_strlen(s1);
	while (s1[a])
		a++;
	if (n < a)
		return (ft_strlen((char *)s2) + n);
	else
	{
		while (a < n - 1 && s2[j])
		{
			s1[a] = s2[j];
			j++;
			a++;
		}
	}
	s1[a] = '\0';
	return (x + ft_strlen((char *)s2));
}
