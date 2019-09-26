#include "minishell.h"

char *handle_tild(t_minishell *sp, char *str)
{
    int x;
    int y;
    char *new;
    // char *tmp = (char *)malloc(sizeof(char));

    y = 0;
    x = 0;
    // int z = 0;
    while (str[y] != '~')
        y++;
    // int store = y;
    new = ft_strdup("HOME=");
    while (sp->environcpy[x])
    {
        if (ft_strncmp(new, sp->environcpy[x], 5) == 0)
            new = ft_strdup(sp->environcpy[x] + 5);
        x++;
    }
    ft_strcpy(str + y, new);
    // free(new);
    return (str);
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
    char *tmp = (char *)malloc(sizeof(char));
    int storex;
    int y;

    x = 0;
    y = 0;
    int z = 0;
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
    while (str[x])
    {
        tmp[z] = str[x];
        z++;
        x++;
    }
    printf("tmp %s\n", tmp);
    x = storex;
    printf("2: %d\n", x);
    printf("%s\n", hold);
    ft_strcat(hold, "=");
    hold = find_env(sp, hold);
    char *s3 = ft_strnew(ft_strlen(hold) + ft_strlen(str - storex));
    ft_strncpy(s3, str, storex);
    s3 = ft_strcat(s3, hold);
    // free(hold);
    return (s3);
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
}

void parse_stdin(t_minishell *sp)
{
    int x;
    sp->ret = (char **)malloc(sizeof(char *));
    sp->ret = ft_strsplit(sp->value, ';');
    x = 0;
    while (sp->ret[x])
    {
        if (ft_strchr(sp->ret[x], '~'))
            sp->ret[x] = handle_tild(sp, sp->ret[x]);
        if (ft_strchr(sp->ret[x], '$'))
            sp->ret[x] = handle_exp(sp, sp->ret[x]);
        printf("s %s\n", sp->ret[x]);
        x++;
    }
}
