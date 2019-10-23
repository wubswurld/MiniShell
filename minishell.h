/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 22:34:53 by jawatter          #+#    #+#             */
/*   Updated: 2019/10/21 22:34:57 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <sys/wait.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>

# define DSP 6
# define QUOTE(x) ((x == '"'))
# define SM_QUOTE(x) ((x == 39))

char			**g_envcpy;

typedef struct		s_minishell
{
	char			*value;
	int				n_flag;
	char			*new;
	char			*path;
	char			**tmp;
	char			**dhole;
	char			**fhold;
	char			*tmp1;
}					t_minishell;

typedef void		(t_dispatcher)(char **cmds, t_minishell *sp);

typedef struct		s_cmd_line
{
	char			*name;
	t_dispatcher	*choosedist;
}					t_cmd_line;

void				is_quote(char *str);
void				fin_env(char **cmds, int x, int val);
int					count_2d(char **str);
int					ft_start(char *s1, char *s2);
int					display();
void				handle_sigint();
int					ft_strccmp(const char *s1, const char *s2, char c);
void				free_2d(char **str);
char				*make_path(char *s1, char *s2);
char				*find_env(char *str);
char				*handle_exp(char *str);
void				handle_quote(char **str, t_minishell *sp);
void				echo(char **cmds, t_minishell *sp);
void				cd(char **cmds, t_minishell *sp);
void				put_env(char **cmds, t_minishell *sp);
void				unset_env(char **cmds, t_minishell *sp);
void				set_env(char **cmds, t_minishell *sp);
char				*rep_dis(t_minishell *sp, char *str);
void				exit_func();
char				*handle_tild(char *str);
void				exec_cmd(t_minishell *sp, char **cmds);
void				handle_cd(char **cmds, char *new, char *tmp);
void				read_stdin(t_minishell *sp);
void				parse_stdin(t_minishell *sp);

#endif
