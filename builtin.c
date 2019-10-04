#include "minishell.h"

void cd(char **cmds, t_minishell *sp)
{
    char *new;
    char *tmp;
    tmp = ft_strdup("OLDPWD=");
    new = ft_strdup("HOME=");
    new = find_env(sp, new);
    if (cmds[1] == NULL || ft_strcmp(cmds[1], "--") == 0)
        chdir(new);
    else if (ft_strcmp(cmds[1], "-") == 0)
    {
        tmp = find_env(sp, tmp);
        chdir(tmp);
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

void handle_quote(char **str, t_minishell *sp)
{
    int x = 1;
    int z = 0;
    x += sp->n_flag;
    while (str[x])
    {
        if (QUOTE(str[x][0]))
        {
            z = 1;
            while (!QUOTE(str[x][z]))
            {
                ft_putchar(str[x][z]);
                z++;
            }
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

void echo(char **cmds, t_minishell *sp)
{
    sp->n_flag = 0;
    if (!cmds[1])
        ft_putchar('\n');
    else if (ft_strcmp(cmds[1], "-n") == 0)
        sp->n_flag = 1;
    handle_quote(cmds, sp);
}