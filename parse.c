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

// go through 2d array of path split
char *get_bin(t_minishell *sp, char **cmds)
{
    char *new;
    char *path;
    struct stat buf;

    new = find_env(sp, ft_strdup("PATH="));
    char **tmp = ft_strsplit(new, ':');
    free(new);
    int y = 0;
    while (tmp[y])
    {
        if (ft_start(cmds[0], tmp[y]))
            path = ft_strdup(cmds[0]);
        else
            path = make_path(tmp[y], cmds[0]);
        if (lstat(path, &buf) != -1)
        {
            free_2d(tmp);
            return (path);
        }
        else
        {
            free(path);
        }
        y++;
    }
    free_2d(tmp);
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
        free(path);
    }
    if (lstat(cmds[0], &buf) != -1)
    {
        if (S_ISDIR(buf.st_mode))
            chdir(cmds[0]);
        else if (S_ISREG(buf.st_mode))
            exec_fork(sp, cmds[0], cmds);
    }
    // else
    // {
    //     ft_putstr("minishell: command not found: ");
    //     ft_putstr(cmds[0]);
    //     ft_putchar('\n');
    // }
    // free_2d(cmds);
}

// if the command is a builtin dispatch it to its function else check if its a executable, regular file or directory
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
                dhole[z] = handle_tild(dhole[z]);
            z++;
        }
        exec_cmd(sp, dhole);
        free_2d(dhole);
        x++;
    }
    free_2d(fhold);
}
