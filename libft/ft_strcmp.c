/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:00:59 by jawatter          #+#    #+#             */
/*   Updated: 2018/11/14 15:01:03 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1 && *s2)
	{
		s2++;
		s1++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
// int ft_strcmp(const char *s1, const char *s2)
// {
// 	unsigned char *c1;
// 	unsigned char *c2;

// 	c1 = (unsigned char *)s1;
// 	c2 = (unsigned char *)s2;
// 	while (*c1 && *c2)
// 	{
// 		if (*c1 != *c2)
// 			return ((*c1 - *c2));
// 		c1++;
// 		c2++;
// 	}
// 	if ((!*c2 && *c1) || (*c2 && !*c1))
// 		return ((*c1 - *c2));
// 	return (0);
// }
