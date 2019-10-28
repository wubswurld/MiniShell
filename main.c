/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 23:37:20 by jawatter          #+#    #+#             */
/*   Updated: 2019/10/20 23:43:22 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//display current working directory and a '>'

int display(void)
{
	char *str;

	str = NULL;
	str = getcwd(str, 1000);
	ft_putstr(str);
	ft_putstr("> ");
	free(str);
	return (0);
}

//copy extern char **environ into 2d array for env related commands

void copy_env(void)
{
	extern char **environ;
	int x;
	int len;

	x = 0;
	len = count_2d(environ);
	g_envcpy = ft_memalloc(sizeof(char *) * (len + 1));
	while (environ[x])
	{
		g_envcpy[x] = ft_strdup(environ[x]);
		x++;
	}
	g_envcpy[x] = NULL;
}

//initialize values and start shell loop
//copy a 2-d array of the extern char **environ, display a prompt,
//read a signle line from stdin using get next line, and start parse, use signal to capture control C

int main(void)
{
	t_minishell sp;

	copy_env();
	sp.value = NULL;
	while (1)
	{
		display();
		signal(SIGINT, handle_sigint);
		get_next_line(0, &(sp.value));
		if (sp.value)
			parse_stdin(&sp);
	}
	free_2d(g_envcpy);
	return (0);
}
