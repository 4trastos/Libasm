/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:34:59 by davgalle          #+#    #+#             */
/*   Updated: 2025/07/09 16:51:23 by davgalle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

extern size_t _ft_strlen(const char *str);
extern  char * _ft_strcpy(char *dst, const char *src);
extern  int _ft_strcmp(const char *s1, const char *s2 );
extern  ssize_t _ft_write(int fd, const void *buf, size_t nbyte);
extern  ssize_t _ft_read(int fd, void *buf, size_t nbyte);
extern char *_ft_strdup(char const *s1);

int main(int argc, char **argv)
{

    if (argc == 1)
    {
        printf("Introduce una cadena de caracteres: \n");
        return (1);
    }
    else
    {
        char *str  = argv[1];
        char *copy; 
        copy = malloc(strlen(argv[1]) + 1);
        if (!copy)
            return (1);
        
        printf("\n######## TEST DE LONGITUD ################## \n");
        printf("El string:  '%s'  ===> Mide:  '%ld'  Bytes en replica Ensamblador\n", str, _ft_strlen(str));
        printf("El string:  '%s'  ===> Mide:  '%ld'  Bytes en STRLEN Original\n", str, strlen(str));
        
        printf("\n######## TEST DE COPIA ################## \n");
        printf("El string Orinal: '%s' =======> La copia con replica Ensamblador: '%s'\n", str, _ft_strcpy(copy, str));
        printf("El string Orinal: '%s' =======> La copia con STRCPY Original: '%s'\n", str, strcpy(copy, str));

        printf("\n######## TEST DE COMPARE IGUALES ################## \n");
        printf("El string Orinal: '%s' =======> Compara copia con replica Ensamblador: '%s' ====> Salida %d\n", str, copy, _ft_strcmp(str, copy));
        printf("El string Orinal: '%s' =======> Compara la copia con STRCMP Original: '%s'  ====> Salida %d\n", str, copy, strcmp(str, copy));

        printf("\n######## TEST DE COMPARE DIFERENTES NEGATIVOS ################## \n");
        printf("El string 'ABCDEF' =======> Compara con replica Ensamblador: 'ABCDFG' ====> Salida %d\n", _ft_strcmp("ABCDEF", "ABCDFG"));
        printf("El string 'ABCDEF' =======> Compara con STRCMP original: 'ABCDFG' ====> Salida %d\n", strcmp("ABCDEF", "ABCDFG"));

        printf("\n######## TEST DE COMPARE DIFERENTES POSITIVOS ################## \n");
        printf("El string 'ABCDEF' =======> Compara con replica Ensamblador: 'ABCDBG' ====> Salida %d\n", _ft_strcmp("ABCDEF", "ABCDBG"));
        printf("El string 'ABCDEF' =======> Compara con STRCMP original: 'ABCDBG' ====> Salida %d\n", strcmp("ABCDEF", "ABCDBG"));
        
        printf("\n######## TEST DE DUPLICATE  ################## \n");
        printf("El string Orinal: '%s' =======> El  duplicado con replica Ensamblador: '%s'\n", str, _ft_strdup(str));
        printf("El string Orinal: '%s' =======> El duplicado con STRDUP Original: '%s'\n", str, strdup(str));
        
        printf("\n######## TEST DE WRITE ################## \n");
        
        ssize_t ret;
        
        // Caso correcto (fd = 1, stdout)
        printf("   Escribiendo por stdout usando _ft_write (fd=1): ");
        ret = _ft_write(1, str, _ft_strlen(str));
        printf("\n_bytes escritos: %zd | errno: %d\n", ret, errno);

        errno = 0;
        printf("   Escribiendo por stdout usando write original (fd=1): ");
        ret = write(1, str, strlen(str));
        printf("\n_bytes escritos: %zd | errno: %d\n", ret, errno);

        // Caso con error (fd = -1)
        errno = 0;
        printf("\nIntentando escribir por fd=-1 usando _ft_write: ");
        ret = _ft_write(-1, str, _ft_strlen(str));
        printf("\n_bytes escritos: %zd | errno: %d (%s)\n", ret, errno, strerror(errno));

        errno = 0;
        printf("Intentando escribir por fd=-1 usando write original: ");
        ret = write(-1, str, strlen(str));
        printf("\n_bytes escritos: %zd | errno: %d (%s)\n", ret, errno, strerror(errno));

        printf("\n######## TEST DE READ ################## \n");
        
        char buffer[100];

        // Caso correcto: leer desde STDIN (fd = 0)
        printf("Introduce algo por teclado (prueba _ft_read): ");
        fflush(stdout); // Forzamos salida antes de leer
        errno = 0;
        ret = _ft_read(0, buffer, sizeof(buffer) - 1);
        if (ret >= 0)
            buffer[ret] = '\0';
        printf("Bytes leídos: %zd | Contenido: \"%s\" | errno: %d\n", ret, buffer, errno);

        printf("Introduce algo por teclado (prueba read original): ");
        fflush(stdout);
        errno = 0;
        ret = read(0, buffer, sizeof(buffer) - 1);
        if (ret >= 0)
            buffer[ret] = '\0';
        printf("Bytes leídos: %zd | Contenido: \"%s\" | errno: %d\n", ret, buffer, errno);

        // Caso con error: fd inválido
        errno = 0;
        ret = _ft_read(-1, buffer, sizeof(buffer) - 1);
        printf("\nProbando _ft_read con fd = -1 ==> Bytes: %zd | errno: %d (%s)\n", ret, errno, strerror(errno));

        errno = 0;
        ret = read(-1, buffer, sizeof(buffer) - 1);
        printf("Probando read original con fd = -1 ==> Bytes: %zd | errno: %d (%s)\n", ret, errno, strerror(errno));

    }

    return (0);
}

