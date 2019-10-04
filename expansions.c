#include "minishell.h"

char *handle_tild(t_minishell *sp, char *str)
{
    int x;
    int y;
    char *new;

    y = 0;
    x = 0;
    while (str[y] != '~')
        y++;
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

char *rep_dis(t_minishell *sp, char *str)
{
    int x = 0;
    char *new;

    while (sp->environcpy[x])
    {
        if (ft_strncmp(str, sp->environcpy[x], 11) == 0)
            new = ft_strdup(sp->environcpy[x] + ft_strlen(str));
        x++;
    }
    ft_strcpy(str, new);
    return (str);
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
    char *new = NULL;
    int x;

    x = 0;
    while (str[x] == '$')
        x++;
    new = ft_strdup(str + x);
    ft_strcat(new, "=");
    new = find_env(sp, new);
    return (new);
}