/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 12:01:19 by jawatter          #+#    #+#             */
/*   Updated: 2018/11/19 15:34:37 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strlen(char *str)
{
	int x;

	x = 0;
	while (str[x] != '\0')
	{
		x++;
	}
	return (x);
}
