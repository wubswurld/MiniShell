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
    char *result;

    s1 = ft_strcat(s1, "/");
    result = ft_strjoin(s1, s2);
    return (result);
}