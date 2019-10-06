#include "minishell.h"

void change_env(t_minishell *sp, char *str)
{
    int x = 0;
    char *old = ft_strdup("OLDPWD=");
    // char *new = ft_strdup("PWD=");
    while (sp->environcpy[x])
    {
        if (ft_strncmp("OLDPWD=", sp->environcpy[x], 7) == 0)
        {
            old = ft_strcat(old, str);
            ft_strcpy(sp->environcpy[x], old);
            free(old);
        }
        x++;
    }
}

void put_env(char **str, t_minishell *sp)
{
    int x;

    x = 0;
    str = NULL;
    while (sp->environcpy[x])
    {
        write(1, sp->environcpy[x], ft_strlen(sp->environcpy[x]));
        ft_putchar('\n');
        x++;
    }
}

void cd(char **cmds, t_minishell *sp)
{
    char *new;
    char *tmp;
    char *hld = NULL;

    tmp = ft_strdup("OLDPWD=");
    new = ft_strdup("HOME=");
    new = find_env(sp, new);
    hld = getcwd(hld, 1000);
    if (cmds[1] == NULL || ft_strcmp(cmds[1], "--") == 0)
        chdir(new);
    else if (ft_strcmp(cmds[1], "-") == 0)
    {
        tmp = find_env(sp, tmp);
        chdir(tmp);
        change_env(sp, hld);
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