#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void double_pointer(char **str, int *len)
{
    int i = 1;
    int x = 0;
    *len = 0;
    while (str[i] != NULL)
    {
        while (str[i][x] != '\0')
        {
            x++;
            (*len)++;
        }
        i++;
        x = 0;
    }
}   

int ft_strlen(char *str)
{
    int len = 0;
    while (str[len] != '\0')
    {
        len++;
    }
    return (len);
}

int main(int argc, char **argv)
{
    int len;

    if (argc < 2)
    {
        write(1, "Por favor, introduce una frase o palabra\n", 41); 
        return (0);
    }
    else if (argc == 2)
    {
        len = ft_strlen(argv[1]);
        printf("El string '%s' mide: %d\n", argv[1], len);
    }
    else
    {
        double_pointer(argv, &len);
        printf("El Frase mide: %d\n", len);
    }
    return (0);
}