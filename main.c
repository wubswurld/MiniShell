#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "minishell.h"

void read_stdin(t_minishell *sp)
{
    int x;
    char ch[10008];
    sp->value = (char *)malloc(sizeof(char));
    while ((x = read(STDIN_FILENO, &ch, 10008)) > 0)
    {
        ch[x] = '\0';
        ft_strcpy(sp->value, ch);
        break;
    }
}

int display()
{
    ft_putchar('>');
    return (0);
}

void init_loop(t_minishell *sp)
{
    while (1)
    {
        display();
        read_stdin(sp);
        printf("here:%s\n", sp->value);
    }
}

int main()
{
    t_minishell *sp;
    sp = (t_minishell *)malloc(sizeof(t_minishell));
    init_loop(sp);
    return (0);
}