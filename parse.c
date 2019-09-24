#include "minishell.h"

void find_env(t_minishell *sp)
{
    int x = 0;
    char *new;

    new = (char *)malloc(sizeof(char));
    while (sp->environcpy[x])
    {
        if (ft_strncmp(sp->str, sp->environcpy[x], 4) == 0)
            new = ft_strdup(sp->environcpy[x] + 4);
        x++;
    }
    ft_strcpy(sp->str, new);
    free(new);
}

void handle_tild(t_minishell *sp)
{
    int x;
    char *new;

    new = (char *)malloc(sizeof(char));
    x = 0;
    new = ft_strdup("HOME=");
    while (sp->environcpy[x])
    {
        if (ft_strncmp(new, sp->environcpy[x], 5) == 0)
            new = ft_strdup(sp->environcpy[x] + 5);
        x++;
    }
    ft_strcpy(sp->str, new);
    printf("%s\n", sp->str);
    free(new);
}

void handle_exp(t_minishell *sp, int y)
{
    int x;
    int storey = 0;
    sp->str = (char *)malloc(sizeof(char));

    storey = y;
    y += 1;
    x = 0;
    while (sp->value[y] != ' ' && sp->value[y])
    {
        sp->str[x] = sp->value[y];
        x++;
        y++;
    }
    ft_strcat(sp->str, "=");
    find_env(sp);
    printf("%s\n", sp->value);
    // sp->value = ft_strsub(sp->str, storey, ft_strlen(sp->str));
    printf("EXP %s\n", sp->value);
    // return (str);
}

void read_stdin(t_minishell *sp)
{
    int x;
    int y;
    char ch;

    y = 0;
    sp->value = (char *)malloc(sizeof(char));
    while ((x = read(STDIN_FILENO, &ch, 1)) && ch != '\n')
        ft_strcat(sp->value, &ch);
    while (sp->value[y])
    {
        if (sp->value[y] == '$')
        {
            handle_exp(sp, y);
        }
        else if (sp->value[y] == '~')
            handle_tild(sp);
        y++;
    }
    printf("input %s\n", sp->value);
}

void parse_stdin(t_minishell *sp)
{
    sp->ret = (char **)malloc(sizeof(char *));
    sp->ret = ft_strsplit(sp->value, ';');
    int x = 0;
    while (sp->ret[x])
    {
        // int y = 0;
        // while (sp->ret[x][y])
        // {
        //     if (sp->ret[x][y] == '$')
        //         handle_exp(sp, y, sp->ret[x]);
        //     // else if (sp->ret[x][y/] == '~')
        //     //  sp->ret[x] = handle_tild(sp, sp->ret[x]);
        // }
        printf("ret %s\n", sp->ret[x]);
        x++;
    }
}
