#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int ft_strcmp(const char *s1, const char *s2)
{
    int i = 0;
    int res = 0;
    while (s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] != s2[i])
        {
            res = s1[i] - s2[i];
            return (res);
        }
        i++;
    }
    if (s1[i] != '\0' || s2[i] != '\0')
        return(res = s1[i] - s2[i]);
    return (res);
}

int main()
{
    const char *str1 = "abcd";
    const char *str2 = "abce";
    int i = 0;

    i = ft_strcmp(str1, str2);
    printf("El resultado es: %d\n", i);
    return (0);
}