#include "minishell.h"

void exit_func()
{
    exit(0);
}

void switch_env(char **tmp)
{
    int q = 0;
    while (tmp[q])
    {
        if (tmp[q])
            envcpy[q] = ft_strdup(tmp[q]);
        q++;
    }
    envcpy[q] = NULL;
}

void unset(char **cmds)
{
    int x = 1;
    int y = 0;
    int val = 0;
    int z = 0;

    char **tmp = ft_memalloc(sizeof(char *) * count_2d(envcpy));
    // cmds[x] = ft_strcat(cmds[x], "=");
    while (envcpy[y])
    {
        if (ft_strccmp(ft_strcat(cmds[x], "="), envcpy[y], '=') == 0)
        {
            val = 1;
            y += 1;
        }
        else
        {
            tmp[z] = ft_strdup(envcpy[y]);
            z++;
        }
        free(envcpy[y]);
        y++;
    }
    switch_env(tmp);
    free_2d(tmp);
}

void unset_env(char **cmds, t_minishell *sp)
{
    char *tmp;

    tmp = NULL;
    sp = NULL;
    if (!cmds[1])
        ft_putstr("unsetenv: too little arguments\n");
    else if (cmds[1] && cmds[2])
        ft_putstr("unsetenv: too many arguments\n");
    else if ((tmp = find_env1(sp, ft_strcat(cmds[1], "="))) != NULL)
    {
        // write(1, "lol\n", 4);
        unset(cmds);
        free(tmp);
    }
    else
        ft_putstr("unsetenv: environment variable not found\n");
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
                free(envcpy[x]);
                val = 1;
                if (cmds[2])
                    envcpy[x] = ft_strdup(ft_strcat(cmds[1], cmds[2]));
                else
                    envcpy[x] = ft_strdup(cmds[1]);
            }
            x++;
        }
        if (val == 0)
        {
            if (cmds[2])
            {
                envcpy[x] = ft_strdup(ft_strcat(cmds[1], cmds[2]));
            }
            else
                envcpy[x] = ft_strdup(cmds[1]);
        }
        envcpy[x + 1] = NULL;
    }
    else
        ft_putstr("setenv: too few arguments\n");
}