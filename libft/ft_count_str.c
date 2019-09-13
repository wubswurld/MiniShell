/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 04:56:30 by jawatter          #+#    #+#             */
/*   Updated: 2018/11/16 04:58:28 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define IS_WHITE(x) (x == '\n' || x == '\t' || x == ' ')

char	*ft_count_str(char *str, int x)
{
	int		y;
	char	*ret;

	y = x;
	if (str[y] == '\0')
	{
		ret = ft_strnew(0);
		ret[0] = '\0';
		return (ret);
	}
	while (str[x])
		x++;
	x--;
	while (IS_WHITE(str[x]))
		x--;
	if (!(ret = (ft_strsub(str, y, x - y + 1))))
		return (NULL);
	return (ret);
}
