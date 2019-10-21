#include "minishell.h"

//display current working directory and a '>'
int display()
{
    char *str = NULL;
    //get current working directory
    str = getcwd(str, 1000);
    ft_putstr(str);
    ft_putstr("> ");
    free(str);
    return (0);
}

//copy extern char **environ into 2d array for env related commands
void copy_env()
{
    extern char **environ;
    int x;

    x = 0;
    int len = count_2d(environ);
    envcpy = ft_memalloc(sizeof(char *) * (len + 1));
    //copy into global 2_d array
    while (environ[x])
    {
        envcpy[x] = ft_strdup(environ[x]);
        x++;
    }
    envcpy[x] = NULL;
}

//free any 2_d array
void free_2d(char **str)
{
    int x = 0;
    while (str[x])
    {
        free(str[x]);
        x++;
    }
    free(str);
}

//initialize values and start shell loop
//copy a 2-d array of the extern char **environ, display a prompt,
//read a signle line from stdin using get next line, and start parse, use signal to capture control C

int main()
{
    t_minishell sp;
    //will memory be null, check if memory is null, when you have memory always nullify
    copy_env();
    while (1)
    {
        display();
        signal(SIGINT, handle_sigint);
        get_next_line(0, &(sp.value));
        //make sure value is not null
        if (sp.value)
            parse_stdin(&sp);
    }
    //free global 2_d array
    // free_2d(envcpy);
    return (0);
}