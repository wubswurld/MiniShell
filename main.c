#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "minishell.h"

void read_stdin(t_minishell *sp)
{
    int x;
    char ch[10008];
    sp->value = (char *)malloc(sizeof(char));
    while (((x = read(STDIN_FILENO, &ch, 10008)) > 0))
    {
        ch[x] = '\0';
        ft_strcpy(sp->value, ch);
        break;
    }
}

int display()
{
    char str[1000 + 1];
    ft_putstr(getcwd(str, 1000));
    ft_putstr("> ");
    return (0);
}

void parse_stdin(t_minishell *sp)
{
    char **ret = (char **)malloc(sizeof(char *));
    ret = ft_strsplit(sp->value, ' ');
    printf("%s\n", ret[0]);
}

void handle_sigint()
{
    ft_putchar('\n');
    display();
}

void init_loop(t_minishell *sp)
{
    while (1)
    {
        display();
        signal(SIGINT, handle_sigint);
        read_stdin(sp);
        parse_stdin(sp);
    }
}

int main()
{
    extern char **environ;
    t_minishell *sp;
    sp = (t_minishell *)malloc(sizeof(t_minishell));
    init_loop(sp);
    return (0);
}