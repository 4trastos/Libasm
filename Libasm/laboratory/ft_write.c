#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

size_t ft_strlen(const char *str);

ssize_t ft_write(int fildes, const void *buf, size_t nbyte);

int main()
{
    const char *str = "Funciono a la perfección\n";
    size_t len = ft_strlen(str);
    ssize_t x = 0;

    x = ft_write(1, str, len);
    printf("Se han printeado: %zd bytes\n", x);
    return(0);
}