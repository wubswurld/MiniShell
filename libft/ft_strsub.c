/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 00:36:00 by jawatter          #+#    #+#             */
/*   Updated: 2018/11/19 22:50:56 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*s1;
	int		x;

	x = 0;
	if (!s)
		return (NULL);
	if (!(s1 = ft_strnew(len)))
		return (NULL);
	return (ft_strncpy(s1, s + start, len));
}
