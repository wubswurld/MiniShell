/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 04:52:57 by jawatter          #+#    #+#             */
/*   Updated: 2018/11/16 04:53:40 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define IS_C(x) (x == c)

int		ft_word(char const *str, char c)
{
	int x;
	int count;
	int k;

	k = 0;
	x = 0;
	count = 0;
	while (str[x])
	{
		if (IS_C(str[x]))
			k = 0;
		else if (!k && str[x])
		{
			k = 1;
			count++;
		}
		x++;
	}
	return (count += 1);
}
