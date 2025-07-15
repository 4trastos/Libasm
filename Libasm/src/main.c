#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

extern size_t _ft_strlen(const char *str);
extern char * _ft_strcpy(char *dst, const char *src);
extern int _ft_strcmp(const char *s1, const char *s2);
extern ssize_t _ft_write(int fd, const void *buf, size_t nbyte);
extern ssize_t _ft_read(int fd, void *buf, size_t nbyte);
extern char * _ft_strdup(const char *s1);

void    option_one(const char *str)
{
    printf("\n_ft_strlen ===>>>> '%s' ===>>>> Mide: '%ld' bytes\n", str, _ft_strlen(str));
    printf("strlen     ===>>>> '%s' ===>>>> Mide: '%ld' bytes\n", str, strlen(str));
}

void    option_two(char *dst, const char *src)
{
    printf("\n_ft_strcpy: Original ===>>>> '%s' ===>>>> Copia: '%s'\n", src, _ft_strcpy(dst, src));
    printf("strcpy:     Original ===>>>> '%s' ===>>>> Copia: '%s'\n", src, strcpy(dst, src));
}

void    option_tree(const char *s1, const char *s2)
{
    printf("\n_ft_strcmp: s1 ===>>>> '%s' ===>>>> s2: '%s'  ===>>>> Salida: '%d'\n", s1, s2, _ft_strcmp(s1, s2));
    printf("strcmp:     s1 ===>>>> '%s' ===>>>> s2: '%s'  ===>>>> Salida: '%d'\n", s1, s2, strcmp(s1, s2));
}

void    option_four(void)
{
    char buffer[1024];
    int fd;
    ssize_t written;

    printf("Introduce el descriptor de archivo (ej. 1 para stdout, 2 para stderr): ");
    if (scanf("%d%*c", &fd) != 1)
    {
        printf("Entrada inválida.\n");
        return;
    }

    printf("Introduce la string a escribir: ");
    if (!fgets(buffer, sizeof(buffer), stdin))
        return;

    buffer[strcspn(buffer, "\n")] = '\0';

    written = _ft_write(fd, buffer, _ft_strlen(buffer));
    printf("\n_ft_write escribió %zd bytes\n", written);
    if (written == -1)
        perror("Error al escribir");

    ssize_t std_written = write(fd, buffer, strlen(buffer));
    printf("\nwrite     escribió %zd bytes\n", std_written);
    if (std_written == -1)
        perror("Error al escribir");
}

void option_five(void)
{
    char path[256];
    char buffer[1024];
    char orig[1024];
    int fd;
    ssize_t bytes_read, std_read;

    printf("Introduce el path del archivo (o 0 para stdin): ");
    if (!fgets(path, sizeof(path), stdin))
        return;
    path[strcspn(path, "\n")] = '\0';

    if (strcmp(path, "0") == 0)
    {
        printf("Escribe algo y pulsa Enter: ");
        fflush(stdout);

        // Leer desde stdin usando _ft_read
        bytes_read = _ft_read(0, buffer, sizeof(buffer) - 1);
        if (bytes_read <= 0)
        {
            perror("_ft_read");
            return;
        }
        buffer[bytes_read] = '\0';

        // Volver a imprimir y pedir la misma entrada para usar read original
        printf("Escribe lo mismo para comparar con read(): ");
        fflush(stdout);
        std_read = read(0, orig, sizeof(orig) - 1);
        if (std_read <= 0)
        {
            perror("read");
            return;
        }
        orig[std_read] = '\0';

        printf("\n_ft_read: leyó ===>>>> '%zd bytes' \n\n\"%s\"\n", bytes_read, buffer);
        printf("\nread:     leyó ===>>>> '%zd bytes' \n\n\"%s\"\n", std_read, orig);
    }
    else
    {
        fd = open(path, O_RDONLY);
        if (fd == -1)
        {
            perror("No se pudo abrir el archivo");
            return;
        }

        bytes_read = _ft_read(fd, buffer, sizeof(buffer) - 1);
        if (bytes_read <= 0)
        {
            perror("_ft_read");
            close(fd);
            return;
        }
        buffer[bytes_read] = '\0';

        lseek(fd, 0, SEEK_SET);
        std_read = read(fd, orig, sizeof(orig) - 1);
        if (std_read <= 0)
        {
            perror("read");
            close(fd);
            return;
        }
        orig[std_read] = '\0';

        printf("\n_ft_read: leyó ===>>>> '%zd bytes' \n\n\"%s\"\n", bytes_read, buffer);
        printf("\nread:     leyó ===>>>> '%zd bytes' \n\n\"%s\"\n", std_read, orig);
        close(fd);
    }
}

void    option_six(const char *s1)
{
    char *copiado = _ft_strdup(s1);
    printf("\n_ft_strdup: s1 ===>>>> '%s' ===>>>> Duplicada: '%s' \n", s1, copiado);
    printf("strdup:     s1 ===>>>> '%s' ===>>>> Duplicada: '%s' \n", s1, strdup(s1));
    if (copiado)
        free(copiado);
    else
        printf("Error al duplicar cadena.\n");
}

void print_menu(void)
{
    printf("\n¿Qué función quieres probar?\n");
    printf("1. ft_strlen\n");
    printf("2. ft_strcpy\n");
    printf("3. ft_strcmp\n");
    printf("4. ft_write\n");
    printf("5. ft_read\n");
    printf("6. ft_strdup\n");
    printf("0. Salir\n");
    printf("Opción: ");
}

int main(int argc, char **argv)
{
    char input[10];
    int option;

    while (1)
    {
        print_menu();

        if (!fgets(input, sizeof(input), stdin))
            continue;

        option = atoi(input);

        if (option == 0)
        {
            printf("Saliendo...\n");
            break;
        }

        if (option == 1)
        {
            char buffer[100];

            printf("Introduce la string a medir: ");
            if (!fgets(buffer, sizeof(buffer), stdin))
                continue;
            buffer[strcspn(buffer, "\n")] = '\0';
            option_one(buffer);
        }
        else if (option == 2)
        {
            char src[100];
            char dst[100];

            printf("Introduce la string a copiar: ");
            if (!fgets(src, sizeof(src), stdin))
                continue;
            src[strcspn(src, "\n")] = '\0';
            option_two(dst, src);

        }
        else if (option == 3)
        {
            char s1[100];
            char s2[100];

            printf("Introduce la string S1: ");
            if (!fgets(s1, sizeof(s1), stdin))
                continue;
            s1[strcspn(s1, "\n")] = '\0';
            printf("Introduce la string S2: ");
            if (!fgets(s2, sizeof(s2), stdin))
                continue;
            s2[strcspn(s2, "\n")] = '\0';
            option_tree(s1, s2);
        }
        else if (option == 4)
        {
            option_four();
        }
        else if (option == 5)
        {
            option_five();
        }
        else if (option == 6)
        {
            char buffer[100];

            printf("Introduce la string a duplicar: ");
            if (!fgets(buffer, sizeof(buffer), stdin))
                continue;
            buffer[strcspn(buffer, "\n")] = '\0';
            option_six(buffer);
        }
        else
        {
            printf("Opción no válida\n");
        }
    }

    return 0;
}
