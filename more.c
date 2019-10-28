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

void echo(char **cmds, t_minishell *sp)
{
	sp->n_flag = 0;
	if (!cmds[1])
		ft_putchar('\n');
	else if (ft_strcmp(cmds[1], "-n") == 0)
		sp->n_flag = 1;
	handle_quote(cmds, sp);
}

void is_quote(char *str)
{
	int z;
	int len;

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

int find_env_pos(char *str)
{
	int x;

	x = 0;
	while (g_envcpy[x])
	{
		if (ft_strccmp(str, g_envcpy[x], '=') == 0)
			return (x);
		x++;
	}
	return (x);
}

char **fix_env(int val)
{
	int x = 0;
	char **tmp = NULL;
	tmp = ft_memalloc(sizeof(char *) * (val + 1));
	while (g_envcpy[x] && x < val)
	{
		tmp[x] = ft_strdup(g_envcpy[x]);
		x++;
	}
	free_2d(g_envcpy);
	return (tmp);
}

void fin_env(char **cmds, int val)
{
	char *tmp;
	tmp = ft_strjoin(cmds[1], "=");
	val = find_env_pos(tmp);
	if (g_envcpy[val] != NULL)
	{
		free(g_envcpy[val]);
		if (cmds[2])
			g_envcpy[val] = ft_strjoin(tmp, cmds[2]);
		else
			g_envcpy[val] = ft_strdup(tmp);
	}
	else
	{
		g_envcpy = fix_env(val + 1);
		if (cmds[2])
			g_envcpy[val] = ft_strjoin(tmp, cmds[2]);
		else
			g_envcpy[val] = ft_strdup(tmp);
	}
	free(tmp);
}