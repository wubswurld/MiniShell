/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 21:52:24 by jawatter          #+#    #+#             */
/*   Updated: 2019/10/21 21:53:06 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_line		g_dispatch_cmd[DSP] = {
	{"echo", &echo},
	{"cd", &cd},
	{"exit", &exit_func},
	{"env", &put_env},
	{"unsetenv", &unset_env},
	{"setenv", &set_env},
};

int		exec_fork(t_minishell *sp, char *path, char **cmds)
{
	pid_t child;

	sp = NULL;
	child = fork();
	if (child == 0)
	{
		execve(path, cmds, g_envcpy);
	}
	else if (child < 0)
	{
		ft_putstr("wubshell could not create process\n");
		return (1);
	}
	wait(&child);
	return (0);
}

char	*get_bin(char **cmds, t_minishell *sp)
{
	int				y;
	struct stat		buf;

	sp->new = find_env("PATH=");
	sp->tmp = ft_strsplit(sp->new, ':');
	free(sp->new);
	y = -1;
	while (sp->tmp[++y])
	{
		if (ft_start(cmds[0], sp->tmp[y]))
			sp->path = ft_strdup(cmds[0]);
		else
			sp->path = make_path(sp->tmp[y], cmds[0]);
		if (lstat(sp->path, &buf) != -1)
		{
			free_2d(sp->tmp);
			return (sp->path);
		}
		else
			free(sp->path);
	}
	free_2d(sp->tmp);
	return (NULL);
}

void	fin_cmd(t_minishell *sp, char **cmds)
{
	char		*path;
	struct stat buf;

	path = get_bin(cmds, sp);
	if (!(lstat(cmds[0], &buf) != -1) && path == NULL)
	{
		ft_putstr("minishell: command not found: ");
		ft_putstr(cmds[0]);
		ft_putchar('\n');
	}
	if (path)
	{
		lstat(cmds[0], &buf);
		exec_fork(sp, path, cmds);
	}
	if (lstat(cmds[0], &buf) != -1)
	{
		if (S_ISDIR(buf.st_mode))
			chdir(cmds[0]);
		else if (S_ISREG(buf.st_mode))
			exec_fork(sp, cmds[0], cmds);
	}
	free(path);
}

void	exec_cmd(t_minishell *sp, char **cmds)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < DSP)
	{
		if (ft_strcmp(cmds[0], g_dispatch_cmd[x].name) == 0)
		{
			g_dispatch_cmd[x].choosedist(cmds, sp);
			y = 1;
		}
		x++;
	}
	if (y == 0)
		fin_cmd(sp, cmds);
}

void	parse_stdin(t_minishell *sp)
{
	int		x;
	int		z;

	x = -1;
	sp->fhold = ft_strsplit(sp->value, ';');
	free(sp->value);
	while (sp->fhold[++x])
	{
		z = -1;
		sp->dhole = ft_strsplit(sp->fhold[x], ' ');
		while (sp->dhole[++z])
		{
			if (ft_strrchr(sp->dhole[z], '$'))
			{
				sp->tmp1 = sp->dhole[z];
				sp->dhole[z] = handle_exp(sp->dhole[z]);
				free(sp->tmp1);
			}
			else if (ft_strchr(sp->dhole[z], '~'))
				sp->dhole[z] = handle_tild(sp->dhole[z]);
		}
		exec_cmd(sp, sp->dhole);
		free_2d(sp->dhole);
	}
	free_2d(sp->fhold);
}
