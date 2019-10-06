#include "minishell.h"

void handle_sigint()
{
    ft_putchar('\n');
    display();
}

int count_2d(char **str)
{
    int x = 0;
    while (str[x])
        x++;
    return (x);
}