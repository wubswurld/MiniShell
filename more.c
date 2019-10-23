/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 21:50:15 by jawatter          #+#    #+#             */
/*   Updated: 2019/10/21 21:50:20 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **cmds, t_minishell *sp)
{
	sp->n_flag = 0;
	if (!cmds[1])
		ft_putchar('\n');
	else if (ft_strcmp(cmds[1], "-n") == 0)
		sp->n_flag = 1;
	handle_quote(cmds, sp);
}

void	is_quote(char *str)
{
	int z;
	int	len;

	len = ft_strlen(str);
	if (str[len - 1] == '"')
	{
		z = 1;
		while (!QUOTE(str[z]))
			ft_putchar(str[z++]);
	}
	else
		ft_putstr("Minishell: Echo: Needed second Quote");
}

void	fin_env(char **cmds, int x, int val)
{
	cmds[1] = ft_strcat(cmds[1], "=");
	while (g_envcpy[++x])
	{
		if (ft_strccmp(cmds[1], g_envcpy[x], '=') == 0)
		{
			free(g_envcpy[x]);
			val = 1;
			if (cmds[2])
				g_envcpy[x] = ft_strdup(ft_strcat(cmds[1], cmds[2]));
			else
				g_envcpy[x] = ft_strdup(cmds[1]);
		}
	}
	if (val == 0)
	{
		if (cmds[2])
			g_envcpy[x] = ft_strdup(ft_strcat(cmds[1], cmds[2]));
		else
			g_envcpy[x] = ft_strdup(cmds[1]);
	}
	g_envcpy[x + 1] = NULL;
}
