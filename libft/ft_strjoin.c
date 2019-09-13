/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 01:09:54 by jawatter          #+#    #+#             */
/*   Updated: 2018/11/11 21:09:55 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	x;
	char	*s3;

	x = 0;
	if (!s1 || !s2)
		return (NULL);
	if (!(s3 = ft_strnew(ft_strlen((char *)s1) + ft_strlen((char *)s2))))
		return (NULL);
	ft_strcpy((char *)s3, (char *)s1);
	s3 = ft_strcat((char *)s3, (char *)s2);
	return (s3);
}
