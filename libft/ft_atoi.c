/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 20:07:08 by jawatter          #+#    #+#             */
/*   Updated: 2018/11/19 12:04:17 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int num;
	int neg;
	int x;

	x = 0;
	neg = 1;
	num = 0;
	while ((str[x] == '\t') || (str[x] == '\n') || (str[x] == '\v') ||
			(str[x] == '\f') || (str[x] == '\r') || (str[x] == ' '))
		x++;
	if (str[x] == '-')
	{
		neg = -1;
		x++;
	}
	else if (str[x] == '+')
		x++;
	while ((str[x] >= '0') && (str[x] <= '9') && (str[x] != '\0'))
	{
		num = (num * 10 + str[x] - '0');
		x++;
	}
	return (num * neg);
}
