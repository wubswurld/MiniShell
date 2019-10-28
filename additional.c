#include "minishell.h"

void free_2d(char **str)
{
    int x;

    x = 0;
    while (str[x])
    {
        free(str[x]);
        x++;
    }
    free(str);
}

//take in the path and a 2_d array of cmds, here we create a child process which is a exact copy of the parent but we are going to use execve to replace it with the once we want if the cmd is not a builtin
int exec_fork(t_minishell *sp, char *path, char **cmds)
{
    pid_t child;

    sp = NULL;
    child = fork();
    //if the child process was created vs if it failed to be created
    if (child == 0)
    {
        execve(path, cmds, g_envcpy);
    }
    else if (child < 0)
    {
        ft_putstr("wubshell could not create process\n");
        return (1);
    }
    wait(&child);
    return (0);
}