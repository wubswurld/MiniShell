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

int exec_fork(t_minishell *sp, char *path, char **cmds)
{
    pid_t child;
    sp = NULL;

    child = fork();
    if (child == 0)
    {
        execve(path, cmds, envcpy);
    }
    else if (child < 0)
    {
        ft_putstr("wubshell could not create process\n");
        return (1);
    }
    wait(&child);
    // free(path);
    return (0);
}

int ft_start(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s2[i])
    {
        if (s1[i] != s2[i])
            return (0);
        i++;
    }
    return (1);
}

char *make_path(char *s1, char *s2)
{
    char *temp;
    char *result;

    temp = ft_strjoin(s1, "/");
    result = ft_strjoin(temp, s2);
    free(temp);
    return (result);
}

//go through 2d array of arguments split by spaces and strcmp the first to check if it is a builtin cmd
// if it is use a dispatch table to go to the cmds execution function
char *get_bin(t_minishell *sp, char **cmds)
{
    char *new;
    char *path;
    struct stat buf;

    char *str = ft_strdup("PATH=");
    new = find_env(sp, str);
    char **tmp = ft_strsplit(new, ':');
    int y = 0;
    while (tmp[y])
    {
        if (ft_start(cmds[0], tmp[y]))
        {
            path = ft_strdup(cmds[0]);
            // printf("path %s\n", path);
        }
        else
            path = make_path(tmp[y], cmds[0]);
        if (lstat(path, &buf) != -1)
        {
            // free_2d(tmp);
            return (path);
        }
        // else
        // {
        //     free(path);
        // }

        y++;
    }
    return (NULL);
}

void fin_cmd(t_minishell *sp, char **cmds)
{
    char *path;
    struct stat buf;

    if ((path = get_bin(sp, cmds)))
    {
        lstat(cmds[0], &buf);
        exec_fork(sp, path, cmds);
    }
    if (lstat(cmds[0], &buf) != -1)
    {
        if (S_ISDIR(buf.st_mode))
            chdir(cmds[0]);
        else if (S_ISREG(buf.st_mode))
            exec_fork(sp, cmds[0], cmds);
    }
    free_2d(cmds);
}

void exec_cmd(t_minishell *sp, char **cmds)
{
    int x = 0;
    int y = 0;
    while (x < DSP)
    {
        if (ft_strcmp(cmds[0], dispatch_cmd[x].name) == 0)
        {
            dispatch_cmd[x].chooseDist(cmds, sp);
            y = 1;
        }
        x++;
    }
    if (y == 0)
        fin_cmd(sp, cmds);
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
    free(sp->value);
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
    free_2d(fhold);
}
