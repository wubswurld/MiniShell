#include "minishell.h"

char *handle_tild(char *str)
{
    int x;
    int y;
    char *new;

    y = 0;
    x = 0;
    while (str[y] != '~')
        y++;
    while (envcpy[x])
    {
        if (ft_strncmp("HOME=", envcpy[x], 5) == 0)
            new = ft_strdup(envcpy[x] + 5);
        x++;
    }
    ft_strcpy(str + y, new);
    free(new);
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

char *rep_dis(t_minishell *sp, char *str)
{
    int x = 0;
    char *new;

    while (sp->environcpy[x])
    {
        if (ft_strncmp(str, envcpy[x], 11) == 0)
            new = ft_strdup(envcpy[x] + ft_strlen(str));
        x++;
    }
    ft_strcpy(str, new);
    free(new);
    return (str);
}

char *find_env1(char *str)
{
    int x = 0;
    char *new = NULL;

    while (envcpy[x])
    {
        if (ft_strccmp(str, envcpy[x], '=') == 0)
            return (ft_strdup(envcpy[x]));
        x++;
    }
    free(new);
    return (NULL);
}

char *find_env(char *str)
{
    int x = 0;

    while (envcpy[x])
    {
        if (ft_strccmp(str, envcpy[x], '=') == 0)
            return (ft_strdup(envcpy[x] + ft_strlen(str)));
        x++;
    }
    return (NULL);
}

char *handle_exp(char *str)
{
    char *new;
    int x;

    x = 0;
    while (str[x] == '$')
        x++;
    new = ft_strnew(ft_strlen(str + x) + 1);
    ft_strcpy(new, str + x);
    ft_strcat(new, "=");
    char *tmp = find_env(new);
    free(new);
    return (tmp);
}