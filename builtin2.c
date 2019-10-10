#include "minishell.h"

void exit_func()
{
    exit(0);
}

void switch_env(char **tmp, t_minishell *sp)
{
    int q = 0;
    sp = NULL;
    while (tmp[q])
    {
        envcpy[q] = ft_strdup(tmp[q]);
        q++;
    }
    free(tmp);
    envcpy[q] = NULL;
}

void unset_env(char **cmds, t_minishell *sp)
{
    int x = 1;
    int y = 0;
    int val = 0;
    int z = 0;
    char **tmp = (char **)malloc(sizeof(char *) * count_2d(envcpy - 1));
    if (cmds[1])
    {
        cmds[x] = ft_strcat(cmds[x], "=");
        while (envcpy[y])
        {
            if (ft_strccmp(cmds[x], envcpy[y], '=') == 0)
            {
                val = 1;
                y += 1;
            }
            else
            {
                tmp[z] = ft_strdup(envcpy[y]);
                z++;
            }
            y++;
        }
        switch_env(tmp, sp);
        if (val == 0)
            ft_putstr("unsetenv: environment variable not found\n");
    }
    else
        ft_putstr("unsetenv: too little arguments\n");
}

void set_env(char **cmds, t_minishell *sp)
{
    int x = 0;
    int val = 0;
    sp = NULL;
    if (cmds[1])
    {
        cmds[1] = ft_strcat(cmds[1], "=");
        while (envcpy[x])
        {
            if (ft_strccmp(cmds[1], envcpy[x], '=') == 0)
            {
                val = 1;
                if (cmds[2])
                    envcpy[x] = ft_strcat(cmds[1], cmds[2]);
                else
                    envcpy[x] = ft_strdup(cmds[1]);
            }
            x++;
        }
        if (val == 0)
        {
            if (cmds[2])
                envcpy[x] = ft_strdup(ft_strcat(cmds[1], cmds[2]));
            else
                envcpy[x] = ft_strdup(cmds[1]);
        }
        envcpy[x + 1] = NULL;
    }
    else
        ft_putstr("setenv: too few arguments\n");
}