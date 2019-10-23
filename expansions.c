/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 22:15:55 by jawatter          #+#    #+#             */
/*   Updated: 2019/10/21 22:16:12 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_tild(char *str)
{
	int		x;
	int		y;
	char	*new;

	y = 0;
	x = 0;
	while (str[y] != '~')
		y++;
	while (g_envcpy[x])
	{
		if (ft_strncmp("HOME=", g_envcpy[x], 5) == 0)
			new = ft_strdup(g_envcpy[x] + 5);
		x++;
	}
	ft_strcpy(str + y, new);
	free(new);
	return (str);
}

int		ft_strccmp(const char *s1, const char *s2, char c)
{
	int		x;

	x = 0;
	if (!c)
		return (0);
	while (s1[x] && s2[x] && s1[x] == s2[x] && s2[x] != '=')
		x++;
	return (((unsigned char *)s1)[x] - ((unsigned char *)s2)[x]);
}

char	*find_env(char *str)
{
	int x;

	x = 0;
	while (g_envcpy[x])
	{
		if (ft_strccmp(str, g_envcpy[x], '=') == 0)
			return (ft_strdup(g_envcpy[x] + ft_strlen(str)));
		x++;
	}
	return (NULL);
}

char	*handle_exp(char *str)
{
	char	*new;
	char	*tmp;
	int		x;

	x = 0;
	while (str[x] == '$')
		x++;
	new = ft_strnew(ft_strlen(str + x) + 1);
	ft_strcpy(new, str + x);
	ft_strcat(new, "=");
	tmp = find_env(new);
	free(new);
	return (tmp);
}
