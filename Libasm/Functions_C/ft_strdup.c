#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int ft_strlen(const char *str)
{
    int i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

char *ft_strdup(const char *s1)
{
    char *new;
    int     i = 0;

    new = (char *)malloc(ft_strlen(s1) + 1);
    if (!new)
        return (NULL);

    while (s1[i] != '\0')
    {
        new[i] = s1[i];
        i++;
    }
    new[i] = '\0';
    return (new);
}

int main()
{
    const char *s1 = "Duplica la frase\n";
    char *new;

    new = ft_strdup(s1);
    printf("- Frase original: %s- Frase copiada: %s", s1, new);
    free (new);
    return (0);
}