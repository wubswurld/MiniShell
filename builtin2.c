/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 22:22:39 by jawatter          #+#    #+#             */
/*   Updated: 2019/10/21 22:22:43 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	switch_env(char **tmp)
{
	int		q;
	int		y;

	q = 0;
	y = 0;
	g_envcpy = ft_memalloc(sizeof(char *) * (count_2d(tmp) + 1));
	while (tmp[q])
	{
		g_envcpy[y] = ft_strdup(tmp[q]);
		q++;
		y++;
	}
	g_envcpy[y] = NULL;
}

void	free_env(char **str)
{
	int		x;

	x = 0;
	while (x < count_2d(g_envcpy))
	{
		free(str[x]);
		x++;
	}
	free(str);
}

void	unset(char *cmds)
{
	int		y;
	int		val;
	int		z;
	char	**tmp;

	y = -1;
	val = 0;
	z = 0;
	tmp = ft_memalloc(sizeof(char *) * (count_2d(g_envcpy) - 1));
	while (g_envcpy[++y])
	{
		if (ft_strccmp(cmds, g_envcpy[y], '=') == 0)
		{
			val = 1;
			y += 1;
		}
		else
		{
			tmp[z] = ft_strdup(g_envcpy[y]);
			z++;
		}
	}
	free_2d(g_envcpy);
	switch_env(tmp);
	free_2d(tmp);
}

void	unset_env(char **cmds, t_minishell *sp)
{
	char	*tmp;

	tmp = NULL;
	sp = NULL;
	if (!cmds[1])
		ft_putstr("unsetenv: too little arguments\n");
	else if (cmds[1] && cmds[2])
		ft_putstr("unsetenv: too many arguments\n");
	else if ((tmp = find_env(ft_strcat(cmds[1], "="))) != NULL)
	{
		unset(cmds[1]);
		free(tmp);
	}
	else
		ft_putstr("unsetenv: environment variable not found\n");
}

void	set_env(char **cmds, t_minishell *sp)
{
	int		x;
	int		val;

	x = -1;
	val = 0;
	sp = NULL;
	if (cmds[1])
		fin_env(cmds, x, val);
	else
		ft_putstr("setenv: too few arguments\n");
}
