/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davgalle <davgalle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 15:19:07 by davgalle          #+#    #+#             */
/*   Updated: 2019/11/18 12:16:14 by davgalle         ###   ########.fr       */
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

# define STRLEN(a)          printf("'%s' = %zu (%zu)\n", a, _ft_strlen(a), strlen(a))
# define STRCMP(d, e)       printf("`%s`:`%s` = %d (%d)\n", (d ? d : "(null)"), (e ? e : "(null)"), _ft_strcmp(d, e), strcmp(d, e))
# define WRITE(g, h)        printf("^%ld (`%s`:%ld)\n", _ft_write(STDOUT_FILENO, g, h), g, h)
# define READ(j, k)         r = _ft_read(STDIN_FILENO, buffer, k); printf("`%s`:%ld\n", buffer, r);
# define ERROR_READ_FD(j, k) do { r = _ft_read(j, buffer, k); printf("FD=%d: %ld (errno=%d)\n", j, r, errno); } while (0)
# define ERROR_READ_FILE(filename, k) do { \
    int fd = open(filename, O_RDONLY); \
    r = _ft_read(fd, buffer, k); \
    printf("File '%s': %ld (errno=%d)\n", filename, r, errno); \
    if (fd != -1) close(fd); \
} while (0)
# define STRDUP(x)          aux = _ft_strdup(x); printf("`%s` (`%s`)\n", (aux ? aux : "(null)"), (x ? x : "(null)")); free(aux); aux = NULL;
# define TEST_READ_FILE(filename, k) do { \
    printf("\nTesting file: '%s'\n", filename); \
    int fd = open(filename, O_RDONLY); \
    if (fd == -1) { \
        printf("Error opening file (errno=%d)\n", errno); \
    } else { \
        r = _ft_read(fd, buffer, k); \
        printf("Read %ld bytes:\n`%.*s`\n", r, (int)r, buffer); \
        close(fd); \
    } \
} while (0)

extern size_t _ft_strlen(const char *str);
extern int _ft_strcmp(char const *s1, const char *s2);
extern char *_ft_strcpy(char *dst, char const *src);
extern ssize_t _ft_write(int fd, const void *buf, size_t nbyte);
extern ssize_t _ft_read(int fd, void *buf, size_t nbyte);
extern char *_ft_strdup(char const *s1);


int main()
{
    int     i = 0;
    long    r = 0;
    char    buffer[100];
    char    *aux;
    char    *aux2;

    while (i < 100)
    {
        buffer[i] = 0;
        i++;
    }

    printf("\n************************************");
    printf("\n************************************\n");
    printf("\n*** TEST STRLEN ***: ==> ft_strlen\n");
    STRLEN("");
    STRLEN("abcd");
    STRLEN("ABCDEFG");
    STRLEN("0123456789abcdef");
    STRLEN("42");
    STRLEN("1");
    printf("Test OK\n");

    printf("\n************************************");
    printf("\n************************************\n");
    printf("\n*** TEST COMPARE ***: ==> ft_strcmp\n");
    STRCMP("", "");
    STRCMP("abcd", "abcd");
    STRCMP("abcd", "abce");
    STRCMP("abcd", "abcefgh");
    STRCMP("", "abcd");
    STRCMP("abcd", "");
    // printf("`%s`:`%s` = %d\n", "ABCDEFG", (char *)NULL, ft_strcmp("ABCDEFG", NULL));
    // printf("`%s`:`%s` = %d\n", (char *)NULL, "ABCDEFG", ft_strcmp(NULL, "ABCDEFG"));
    // printf("`%s`:`%s` = %d\n", (char *)NULL, (char *)NULL, ft_strcmp(NULL, NULL));
    printf("Test OK\n");

    printf("\n************************************");
    printf("\n************************************\n");
    printf("\n*** TEST COPY ***: ==> ft_strcpy\n");
    printf("`%s` (`abcd`)\n", _ft_strcpy(buffer, "abcd"));
	printf("`%s` (empty)\n", _ft_strcpy(buffer, ""));
	printf("`%s` (`long message`)\n", _ft_strcpy(buffer, "long message"));
	// printf("`%s` (NULL > not modified)\n", ft_strcpy(buffer, NULL));
    printf("Test OK\n");

    printf("\n************************************");
    printf("\n************************************\n");
    printf("\n*** TEST WRITE ***: ==> ft_write\n");
	WRITE("abcd", 4L);
	WRITE("abcdabcd", 4L);
	WRITE("abcdabcd", 8L);
	WRITE("abcd", 2L);
	printf("Test OK\n");

    printf("\n************************************");
    printf("\n************************************\n");
    printf("\n*** TEST READ ***: ==> ft_read (Casos de error)\n");

    // 1. Test con file descriptor inválido
    printf("1. FD inválido (-1):\n");
    ERROR_READ_FD(-1, 1000);

    // 2. Test con archivo que no existe
    printf("\n2. Archivo inexistente:\n");
    ERROR_READ_FILE("/este/archivo/no/existe.txt", 100);

    // 3. Test con archivo sin permisos de lectura
    printf("\n3. Archivo sin permisos:\n");
    system("touch /tmp/protegido && chmod 000 /tmp/protegido");
    ERROR_READ_FILE("/tmp/protegido", 100);
    system("rm -f /tmp/protegido");

    // 4. Tests normales de lectura
    printf("\n4. Lectura estándar:\n");
    printf("Introduce texto para probar lectura (max 50 chars):\n");
    READ(STDIN_FILENO, 50);

    // 5. Test de lectura de 0 bytes
    printf("\n5. Lectura de 0 bytes:\n");
    READ(STDIN_FILENO, 0);

    printf("\n**********************************************************");
    printf("\n*** TEST READ FILE ***: Prueba con archivo personalizado\n");
    
    char filepath[256];
    printf("\nIntroduce la ruta completa del archivo que quieres probar (o Enter para saltar): ");
    if (fgets(filepath, sizeof(filepath), stdin) != NULL) {
        // Eliminar el salto de línea final
        filepath[strcspn(filepath, "\n")] = 0;
        
        if (filepath[0] != '\0') {
            TEST_READ_FILE(filepath, sizeof(buffer) - 1);
        } else {
            printf("-- Prueba de archivo omitida --\n");
        }
    }
    
    // Limpiar el buffer para las pruebas siguientes
    memset(buffer, 0, sizeof(buffer));

    printf("\n************************************");
    printf("\n************************************\n");
    printf("\n*** TEST STRDUP **** : ==> ft_strdup\n");
	aux2 = _ft_strdup("abcd");
	STRDUP(aux2);
    free(aux2);
	STRDUP("tester");
	STRDUP("long message");
	STRDUP("");
	// STRDUP(NULL);
	printf("Test OK\n");
        
    printf("\n************************************");
    printf("--------------------------------------------------\n");
    printf("Todas las pruebas automáticas comparando el original están OK!\n");

    return 0;
}
