#include "minishell.h"

char *handle_tild(t_minishell *sp)
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
    return (new);
}

int ft_strccmp(const char *s1, const char *s2, char c)
{
    int x;

    x = 0;
    if (!c)
        return (0);
    while (s1[x] && s2[x] && s1[x] == s2[x] && s2[x] != '=')
        x++;
    return (((unsigned char *)s1)[x] - ((unsigned char *)s2)[x]);
}

char *find_env(t_minishell *sp, char *str)
{
    int x = 0;
    char *new;

    // new = (char *)malloc(sizeof(char));
    while (sp->environcpy[x])
    {
        if (ft_strccmp(str, sp->environcpy[x], '=') == 0)
            new = ft_strdup(sp->environcpy[x] + ft_strlen(str));
        x++;
    }
    ft_strcpy(str, new);
    return (str);
}

char *handle_exp(t_minishell *sp, char *str)
{
    int x;
    char *hold = (char *)malloc(sizeof(char));
    int storex;
    int y;

    x = 0;
    y = 0;
    while (str[x] != '$')
        x++;
    storex = x;
    x += 1;
    while (str[x] != ' ' && str[x] != ';' && str[x])
    {
        hold[y] = str[x];
        x++;
        y++;
    }
    ft_strcat(hold, "=");
    printf("hold %s\n", hold);
    hold = find_env(sp, hold);
    printf("hold %s\n", hold);
    char *s3 = ft_strnew(ft_strlen(hold) + ft_strlen(str - storex));
    ft_strncpy(s3, str, storex);
    printf("s3 %s\n", s3);
    s3 = ft_strcat(s3, hold);
    // free(hold);
    return (s3);
}

// void handle_exp(t_minishell *sp, int y)
// {
//     int x;
//     int storey = 0;
// sp->str = (char *)malloc(sizeof(char));
//     storey = y;
//     y += 1;
//     x = 0;
//     while (sp->value[y] != ' ' && sp->value[y])
//     {
// sp->str[x] = sp->value[y];
// x++;
// y++;
//     }
//     ft_strcat(sp->str, "=");
// find_env(sp);
// sp->value = havi(sp->value, sp->str, y);
// ft_strcpy(sp->value + storey, sp->str);
// sp->value = ft_strsub(sp->str, storey, ft_strlen(sp->str));
// printf("sp->str %s\n", sp->str);
// printf("sp->value %s\n", sp->value);
// return (str);
// }

void read_stdin(t_minishell *sp)
{
    int x;
    int y;
    char ch;

    y = 0;
    sp->value = (char *)malloc(sizeof(char));
    while ((x = read(STDIN_FILENO, &ch, 1)) && ch != '\n')
        ft_strcat(sp->value, &ch);
}

void parse_stdin(t_minishell *sp)
{
    sp->ret = (char **)malloc(sizeof(char *));
    sp->ret = ft_strsplit(sp->value, ';');
    // int x = 0;
    sp->hld = 0;
    while (sp->ret[sp->hld])
    {
        if (ft_strchr(sp->ret[sp->hld], '$'))
            sp->ret[sp->hld] = handle_exp(sp, sp->ret[sp->hld]);
        else if (ft_strchr(sp->ret[sp->hld], '~'))
            sp->ret[sp->hld] = handle_tild(sp);
        printf("%s\n%d\n", sp->ret[sp->hld], sp->hld);
        sp->hld++;
    }
}
