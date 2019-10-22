#include "minishell.h"

//print list of env vars copied earlier
void put_env(char **str, t_minishell *sp)
{
    int x;

    x = 0;
    str = NULL;
    sp = NULL;
    while (envcpy[x])
    {
        ft_putstr(envcpy[x]);
        ft_putchar('\n');
        x++;
    }
}

//set paths for cd -
void change_env(t_minishell *sp, char *str)
{
    int x = 0;
    sp = NULL;
    char *old = ft_strdup("OLDPWD=");
    while (envcpy[x])
    {
        if (ft_strncmp("OLDPWD=", envcpy[x], 7) == 0)
        {
            old = ft_strcat(old, str);
            ft_strcpy(envcpy[x], old);
        }
        x++;
    }
    free(old);
}
//set Home path for cd '~', change dir and oldpwd for cd -
// else just cd into the second arg
void cd(char **cmds, t_minishell *sp)
{
    char *new = NULL;
    char *tmp;
    char *hld = NULL;

    sp = NULL;
    hld = getcwd(hld, 1000);
    if (cmds[1] == NULL || ft_strcmp(cmds[1], "--") == 0)
    {
        new = find_env("HOME=");
        chdir(new);
        free(new);
    }
    else if (ft_strcmp(cmds[1], "-") == 0)
    {
        tmp = find_env("OLDPWD=");
        if (chdir(tmp) == 0)
        {
            ft_putstr(tmp);
            ft_putchar('\n');
            // change_env(sp, hld);
        }
        free(tmp);
    }
    else if (cmds[1] && cmds[2] == NULL)
    {
        chdir(cmds[1]);
    }
    else if (cmds[1] && cmds[2])
    {
        ft_putstr("cd: string not in pwd: ");
        ft_putstr(cmds[1]);
        ft_putchar('\n');
    }
    free(hld);
}

int check_quote(char *str)
{
    int x = 1;
    while (str[x])
    {
        if (str[x] == '"')
            return (0);
        x++;
    }
    return (1);
}

//parse arguments for quotes expansions arent handled inside of quotes
void handle_quote(char **str, t_minishell *sp)
{
    int x = 1;
    int z = 0;
    x += sp->n_flag;
    while (str[x])
    {
        if (QUOTE(str[x][0]))
        {
            if (check_quote(str[x]))
            {
                z = 1;
                while (!QUOTE(str[x][z]))
                    ft_putchar(str[x][z++]);
                if (str[x + 1])
                    ft_putchar(' ');
            }
            // if (!(check_quote(str[x])))
            // {
            // ft_putstr("Minishell: Echo: Needed second Quote\n");
            // }
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

//handle echo and -n flag and check quotes
void echo(char **cmds, t_minishell *sp)
{
    sp->n_flag = 0;
    if (!cmds[1])
        ft_putchar('\n');
    else if (ft_strcmp(cmds[1], "-n") == 0)
        sp->n_flag = 1;
    handle_quote(cmds, sp);
}