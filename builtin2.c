#include "minishell.h"

void exit_func()
{
    exit(0);
}

void switch_env(char **tmp, t_minishell *sp)
{
    int q = 0;
    while (tmp[q])
    {
        sp->environcpy[q] = ft_strdup(tmp[q]);
        q++;
    }
    sp->environcpy[q] = NULL;
}

void unset_env(char **cmds, t_minishell *sp)
{
    int x = 1;
    int y = 0;
    int val = 0;
    int z = 0;
    char **tmp = (char **)malloc(sizeof(char *) * count_2d(sp->environcpy - 1));
    if (cmds[1])
    {
        cmds[x] = ft_strcat(cmds[x], "=");
        while (sp->environcpy[y])
        {
            if (ft_strccmp(cmds[x], sp->environcpy[y], '=') == 0)
            {
                val = 1;
                y += 1;
            }
            else
            {
                tmp[z] = ft_strdup(sp->environcpy[y]);
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
    if (cmds[1])
    {
        cmds[1] = ft_strcat(cmds[1], "=");
        while (sp->environcpy[x])
        {
            if (ft_strccmp(cmds[1], sp->environcpy[x], '=') == 0)
            {
                val = 1;
                if (cmds[2])
                    sp->environcpy[x] = ft_strcat(cmds[1], cmds[2]);
                else
                    sp->environcpy[x] = ft_strdup(cmds[1]);
                // x += 1;
            }
            x++;
        }
        if (val == 0)
        {
            if (cmds[2])
                sp->environcpy[x] = ft_strdup(ft_strcat(cmds[1], cmds[2]));
            else
                sp->environcpy[x] = ft_strdup(cmds[1]);
        }
        sp->environcpy[x + 1] = NULL;
    }
    else
        ft_putstr("setenv: too few arguments\n");
}