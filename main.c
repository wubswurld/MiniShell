#include "minishell.h"

//display current working directory
int display()
{
    char *str = NULL;
    str = getcwd(str, 1000);
    ft_putstr(str);
    ft_putstr("> ");
    return (0);
}

//copy extern char **environ into 2d array for env related commands
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

//copy a 2-d array of the extern char **environ, display a prompt,
//read a signle line from stdin using get next line, and start parse, use signal to capture control C

void init_loop(t_minishell *sp)
{
    copy_env(sp);
    while (1)
    {
        display();
        signal(SIGINT, handle_sigint);
        get_next_line(0, &sp->value);
        parse_stdin(sp);
    }
}

void free_file(t_minishell *sp)
{
    int x = 0;
    while (sp->environcpy[x])
    {
        free(sp->environcpy[x]);
        x++;
    }
    free(sp->environcpy);
    free(sp->value);
}

//initialize values and start shell loop
int main()
{
    t_minishell *sp;

    sp = (t_minishell *)malloc(sizeof(t_minishell));
    sp->value = (char *)malloc(sizeof(char));
    init_loop(sp);
    // free_file(sp);
    return (0);
}