#include "minishell.h"

int display()
{
    char str[1000 + 1];
    ft_putstr(getcwd(str, 1000));
    ft_putstr("> ");
    return (0);
}

void handle_sigint()
{
    ft_putchar('\n');
    display();
}

int count_2d(char **str)
{
    int x = 0;
    while (str[x])
        x++;
    return (x);
}

void copy_env(t_minishell *sp)
{
    extern char **environ;
    int x;

    x = 0;
    sp->environcpy = (char **)malloc(sizeof(char *) * (count_2d(environ)));
    while (environ[x])
    {
        sp->environcpy[x] = ft_strdup(environ[x]);
        x++;
    }
    sp->environcpy[x] = NULL;
}

void init_loop(t_minishell *sp)
{
    copy_env(sp);
    while (1)
    {
        display();
        // signal(SIGINT, handle_sigint);
        read_stdin(sp);
        parse_stdin(sp);
    }
}

int main()
{
    t_minishell *sp;
    sp = (t_minishell *)malloc(sizeof(t_minishell));
    init_loop(sp);
    return (0);
}