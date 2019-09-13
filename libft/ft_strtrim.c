/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 14:41:57 by jawatter          #+#    #+#             */
/*   Updated: 2018/11/16 04:57:24 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define IS_WHITE(x) (x == '\n' || x == '\t' || x == ' ')

char			*ft_strtrim(char const *s)
{
	char	*str;

	if (!s)
		return (NULL);
	str = ft_count_str((char *)s, ft_count_w((char *)s));
	return (str);
}
