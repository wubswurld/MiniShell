#include "minishell.h"

// builtin functions accessed through cmd[0] being compared to the name
t_cmd_line dispatch_cmd[DSP] = {
    {"echo", &echo},
    {"cd", &cd},
    {"exit", &exit_func},
    {"env", &put_env},
    {"unsetenv", &unset_env},
    {"setenv", &set_env},
};

//go through 2d array of arguments split by spaces and strcmp the first to check if it is a builtin cmd
// if it is use a dispatch table to go to the cmds execution function

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

// split line read from stdin into arguments by the ';' then split it by spaces to handle expansions
// iterate through your arguments which are split by spaces and handle for expansions if '~' or '$' is found
// cd $PWD; becomes cd | $PWD iterate through the second 2d array and check for expansions
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
