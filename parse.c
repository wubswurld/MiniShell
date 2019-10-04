#include "minishell.h"

void exit_func()
{
    exit(0);
}

t_cmd_line dispatch_cmd[DSP] = {
    {"echo", &echo},
    {"cd", &cd},
    {"exit", &exit_func},
};

void exec_cmd(t_minishell *sp, char **cmds)
{
    int x = 0;
    while (x < DSP)
    {
        if (ft_strcmp(cmds[0], dispatch_cmd[x].name) == 0)
            dispatch_cmd[x].chooseDist(cmds, sp);
        x++;
    }
}

void parse_stdin(t_minishell *sp)
{
    int x;
    int z;
    char **dhole;
    char **fhold;

    x = 0;
    fhold = ft_strsplit(sp->value, ';');
    while (fhold[x])
    {
        z = 0;
        dhole = ft_strsplit(fhold[x], ' ');
        while (dhole[z])
        {
            if (ft_strrchr(dhole[z], '$'))
                dhole[z] = handle_exp(sp, dhole[z]);
            else if (ft_strchr(dhole[z], '~'))
                dhole[z] = handle_tild(sp, dhole[z]);
            z++;
        }
        exec_cmd(sp, dhole);
        x++;
    }
}
