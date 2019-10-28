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

// builtin functions accessed through cmd[0] being compared to the name

t_cmd_line g_dispatch_cmd[DSP] = {
	{"echo", &echo},
	{"cd", &cd},
	{"exit", &exit_func},
	{"env", &put_env},
	{"unsetenv", &unset_env},
	{"setenv", &set_env},
};

// go through 2d array of path split

char *get_bin(char **cmds, t_minishell *sp)
{
	//find path env and split it at each ':', if the executable is not in the path, add a '/' and concatenate it to the end
	//funky implementation but neccessary to prevent segfaults when path env is not present
	sp->y = 0;
	if ((sp->new = find_env("PATH=")) != NULL)
	{
		sp->tmp = ft_strsplit(sp->new, ':');
		free(sp->new);
	}
	else
		return (NULL);
	while (sp->tmp[sp->y])
	{
		if (ft_start(cmds[0], sp->tmp[sp->y]))
			sp->path = ft_strdup(cmds[0]);
		else
			sp->path = make_path(sp->tmp[sp->y], cmds[0]);
		if (lstat(sp->path, &sp->buf) != -1)
		{
			free_2d(sp->tmp);
			return (sp->path);
		}
		else
			free(sp->path);
		sp->y++;
	}
	free_2d(sp->tmp);
	return (NULL);
}

//if the executable is not found in the path it has to be a directory or a exe like ./a.out

void fin_cmd(t_minishell *sp, char **cmds)
{
	char *path;
	struct stat buf;

	path = get_bin(cmds, sp);
	if (!(lstat(cmds[0], &buf) != -1) && path == NULL)
	{
		ft_putstr("minishell: command not found: ");
		ft_putstr(cmds[0]);
		ft_putchar('\n');
	}
	else if (path)
	{
		lstat(cmds[0], &buf);
		exec_fork(sp, path, cmds);
	}
	else if (lstat(cmds[0], &buf) != -1)
	{
		if (S_ISDIR(buf.st_mode))
			chdir(cmds[0]);
		else if (S_ISREG(buf.st_mode))
			exec_fork(sp, cmds[0], cmds);
	}
	free(path);
}

// if the command is a builtin dispatch it to its function else check if its a executable, regular file or directory

void exec_cmd(t_minishell *sp, char **cmds)
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

// split line read from stdin into arguments by the ';' then split it by spaces to handle expansions
// iterate through your arguments which are split by spaces and handle for expansions if '~' or '$' is found
// cd $PWD; becomes a 2_d array like so | cd | $PWD | iterate through this 2d array and check for expansions

void parse_stdin(t_minishell *sp)
{
	int x;
	int z;

	x = -1;
	sp->fhold = ft_strsplit(sp->value, ';');
	free(sp->value);
	while (sp->fhold[++x])
	{
		z = -1;
		sp->split = ft_strsplit(sp->fhold[x], ' ');
		while (sp->split[++z])
		{
			if (ft_strrchr(sp->split[z], '$'))
			{
				sp->tmp1 = sp->split[z];
				sp->split[z] = handle_exp(sp->split[z]);
				free(sp->tmp1);
			}
			else if (ft_strchr(sp->split[z], '~'))
				sp->split[z] = handle_tild(sp->split[z]);
		}
		if (sp->split[0])
			exec_cmd(sp, sp->split);
		free_2d(sp->split);
	}
	free_2d(sp->fhold);
}
