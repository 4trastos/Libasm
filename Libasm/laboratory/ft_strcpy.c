#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int ft_strlen(const char *str)
{
    int len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return (len);
}

char *ft_strcpy(char *dst, const char *src)
{
    int i = 0;
    while (src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return (dst);
}

int main()
{
    const char *test = "Texto para copiar\n";
    char *copy;
    int len = 0;

    len = ft_strlen(test);
    copy = (char *)malloc(len * 1);
    if (!copy)
        return (1);

    ft_strcpy(copy, test);
    printf("El mensaje original es: %s y se ha copiado: %s", test, copy);
    free (copy);

    return (0);
}