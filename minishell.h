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

typedef struct s_minishell
{
    char *value;
    char **environcpy;
    char *str;
    char **ret;
} t_minishell;

void read_stdin(t_minishell *sp);
void parse_stdin(t_minishell *sp);
#endif
