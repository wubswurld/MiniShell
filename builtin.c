/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 23:43:53 by jawatter          #+#    #+#             */
/*   Updated: 2019/10/20 23:45:31 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_env(t_minishell *sp, char *str)
{
	int		x;
	char	*old;

	sp = NULL;
	old = ft_strdup("OLDPWD=");
	x = 0;
	while (g_envcpy[x])
	{
		if (ft_strncmp("OLDPWD=", g_envcpy[x], 7) == 0)
		{
			old = ft_strcat(old, str);
			ft_strcpy(g_envcpy[x], old);
		}
		x++;
	}
	free(old);
}

void	put_env(char **str, t_minishell *sp)
{
	int	x;

	x = 0;
	str = NULL;
	sp = NULL;
	while (g_envcpy[x])
	{
		ft_putstr(g_envcpy[x]);
		ft_putchar('\n');
		x++;
	}
}

void	handle_cd(char **cmds, char *new, char *tmp)
{
	if (cmds[1] == NULL || ft_strcmp(cmds[1], "--") == 0)
	{
		new = find_env("HOME=");
		chdir(new);
		free(new);
	}
	else if (ft_strcmp(cmds[1], "-") == 0)
	{
		tmp = find_env("OLDPWD=");
		chdir(tmp);
		ft_putstr(tmp);
		ft_putchar('\n');
		free(tmp);
	}
	else if (cmds[1] && cmds[2] == NULL)
		chdir(cmds[1]);
	else if (cmds[1] && cmds[2])
	{
		ft_putstr("cd: string not in pwd: ");
		ft_putstr(cmds[1]);
		ft_putchar('\n');
	}
}

void	cd(char **cmds, t_minishell *sp)
{
	char *new;
	char *tmp;
	char *hld;

	sp = NULL;
	new = NULL;
	hld = NULL;
	tmp = NULL;
	hld = getcwd(hld, 1000);
	handle_cd(cmds, new, tmp);
	free(hld);
}

void	handle_quote(char **str, t_minishell *sp)
{
	int x;

	x = 1;
	x += sp->n_flag;
	while (str[x])
	{
		if (QUOTE(str[x][0]))
		{
			is_quote(str[x]);
			if (str[x + 1])
				ft_putchar(' ');
		}
		else
		{
			ft_putstr(str[x]);
			if (str[x + 1])
				ft_putchar(' ');
		}
		x++;
	}
	if (sp->n_flag == 0 && str[1])
		ft_putchar('\n');
}
