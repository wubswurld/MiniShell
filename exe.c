#include "minishell.h"

// //go through 2d array of arguments split by spaces and strcmp the first to check if it is a builtin cmd
// // if it is use a dispatch table to go to the cmds execution function

// void exec_cmd(t_minishell *sp, char **cmds)
// {
//     int x = 0;
//     char *new = ft_strdup("PATH=");
//     while (x < DSP)
//     {
//         if (ft_strcmp(cmds[0], dispatch_cmd[x].name) == 0)
//             dispatch_cmd[x].chooseDist(cmds, sp);
//         x++;
//     }
//     if (x == DSP)
//     {
//         new = find_env(sp, new);
//         char **tmp = ft_strsplit(new, ':');
//         int y = 0;
//         while (tmp[y])
//         {
//             if (ft_starts_with(cmds[0], tmp[y]))
//                 tmp[y] = ft_strdup(cmds[0]);
//         }
//         // exec_fork(cmds);
//     }
// }