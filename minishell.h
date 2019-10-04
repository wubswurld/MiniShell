#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft/libft.h"
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#define DSP 3
#define QUOTE(x) ((x == '"'))

typedef struct s_minishell
{
    char *value;
    char **environcpy;
    char *str;
    char **ret;
    int hld;
    int n_flag;
} t_minishell;

typedef void(dispatcher)(char **cmds, t_minishell *sp);

typedef struct s_cmd_line
{
    char *name;
    dispatcher *chooseDist;
} t_cmd_line;

void cd();
void echo();
void read_stdin(t_minishell *sp);
void parse_stdin(t_minishell *sp);
char *handle_tild(t_minishell *sp, char *str);
int ft_strccmp(const char *s1, const char *s2, char c);
char *find_env(t_minishell *sp, char *str);
char *handle_exp(t_minishell *sp, char *str);
void handle_quote(char **str, t_minishell *sp);
void echo(char **cmds, t_minishell *sp);
void cd(char **cmds, t_minishell *sp);
char *rep_dis(t_minishell *sp, char *str);
void exit_func();

#endif
