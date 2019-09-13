/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 21:23:44 by jawatter          #+#    #+#             */
/*   Updated: 2018/11/19 12:05:40 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define IS_C(x) (x == c)
#define NOT_C(x) (x != c)

char	**ft_strsplit(char const *s, char c)
{
	int			a;
	int			i;
	char		**head;
	int			x;

	x = 0;
	i = 0;
	if (!(s) || !(head = (char **)malloc((ft_word(s, c)) * sizeof(char *))))
		return (NULL);
	while (s[i])
	{
		a = 0;
		while (IS_C(s[i]) && s[i])
			i++;
		if (ft_subcount(s, i, c) != 0)
		{
			head[x] = ft_strnew(ft_subcount(s, i, c) + 1);
			while (NOT_C(s[i]) && s[i])
				head[x][a++] = s[i++];
			head[x++][a] = '\0';
		}
	}
	head[x] = 0;
	return (head);
}
