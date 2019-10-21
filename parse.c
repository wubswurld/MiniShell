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

//take in the path and a 2_d array of cmds, here we create a child process which is a exact copy of the parent but we are going to use execve to replace it with the once we want if the cmd is not a builtin

int exec_fork(t_minishell *sp, char *path, char **cmds)
{
    pid_t child;
    sp = NULL;

    child = fork();
    //if the child process was created vs if it failed to be created
    if (child == 0)
    {
        execve(path, cmds, envcpy);
    }
    else if (child < 0)
    {
        ft_putstr("wubshell could not create process\n");
        return (1);
    }
    //makes the parent process wait until the child process has been terminated
    wait(&child);
    return (0);
}

// go through 2d array of path split
char *get_bin(char **cmds)
{
    char *new;
    char *path;
    struct stat buf;

    //find path env and split it at each ':'
    new = find_env("PATH=");
    char **tmp = ft_strsplit(new, ':');
    free(new);
    int y = -1;
    //iterate through 2_d array of path, if cmds[0] matches tmp[y] strdup cmds[0] else add the cmd to the end of the /bin path if the file cannot be lstated it is not a executable
    while (tmp[++y])
    {
        if (ft_start(cmds[0], tmp[y]))
            path = ft_strdup(cmds[0]);
        else
            path = make_path(tmp[y], cmds[0]);
        //lstat path created
        if (lstat(path, &buf) != -1)
        {
            free_2d(tmp);
            return (path);
        }
        else
        {
            free(path);
        }
        // y++;
    }
    free_2d(tmp);
    return (NULL);
}

void fin_cmd(t_minishell *sp, char **cmds)
{
    char *path;
    struct stat buf;
    path = get_bin(cmds);
    if (!(lstat(cmds[0], &buf) != -1) && path == NULL)
    {
        ft_putstr("minishell: command not found: ");
        ft_putstr(cmds[0]);
        ft_putchar('\n');
    }
    if (path)
    {
        lstat(cmds[0], &buf);
        exec_fork(sp, path, cmds);
    }
    //if the executable is not found in the path it has to be a directory or a exe like ./a.out
    if (lstat(cmds[0], &buf) != -1)
    {
        //checks if its a directory or regular file
        if (S_ISDIR(buf.st_mode))
            chdir(cmds[0]);
        else if (S_ISREG(buf.st_mode))
            exec_fork(sp, cmds[0], cmds);
    }
    free(path);
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
// cd $PWD; becomes a 2_d array like so | cd | $PWD | iterate through this 2d array and check for expansions
void parse_stdin(t_minishell *sp)
{
    int x;
    int z;
    char **dhole;
    char **fhold;

    x = -1;
    //split entire args by ';' so cd $PWD; ls becomes | cd $PWD | ls in a 2_d array and free value passed in from getnextline
    fhold = ft_strsplit(sp->value, ';');
    free(sp->value);
    while (fhold[++x])
    {
        z = -1;
        // split each argument which is now in a row in a 2_d array into a new 2_d array split from each space
        dhole = ft_strsplit(fhold[x], ' ');
        //iterate through that 2_d array and swap in any expansion
        while (dhole[++z])
        {
            if (ft_strrchr(dhole[z], '$'))
            {
                char *tmp = dhole[z];
                dhole[z] = handle_exp(dhole[z]);
                free(tmp);
            }
            else if (ft_strchr(dhole[z], '~'))
                dhole[z] = handle_tild(dhole[z]);
        }
        exec_cmd(sp, dhole);
        free_2d(dhole);
    }
    free_2d(fhold);
}
