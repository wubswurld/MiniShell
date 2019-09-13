/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 01:22:40 by jawatter          #+#    #+#             */
/*   Updated: 2018/11/19 22:35:34 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s1, char (*f)(unsigned int, char))
{
	int		x;
	char	*wubs;

	x = 0;
	if (!s1 || !f)
		return (NULL);
	if (!(wubs = (char *)malloc(ft_strlen((char *)s1) + 1)))
		return (NULL);
	while (s1[x] != '\0')
	{
		wubs[x] = f(x, s1[x]);
		x++;
	}
	wubs[x] = '\0';
	return (wubs);
}
