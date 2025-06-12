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

# define STRLEN(a)          printf("'%s' = %zu (%zu)\n", a, ft_strlen(a), strlen(a));
# define STRCMP(d, e)       printf("`%s`:`%s` = %d (%d)\n", (d ? d : "(null)"), (e ? e : "(null)"), ft_strcmp(d, e), strcmp(d, e));
# define WRITE(g, h)        printf("^%ld (`%s`:%ld)\n", ft_write(STDOUT_FILENO, g, h), g, h);
# define READ(j, k)         r = ft_read(STDIN_FILENO, buffer, k); printf("`%s`:%ld\n", buffer, r);
# define STRDUP(x)          aux = ft_strdup(x); printf("`%s` (`%s`)\n", (aux ? aux : "(null)"), (x ? x : "(null)")); free(aux); aux = NULL;


extern size_t ft_strlen(const char *str);
extern int ft_strcmp(char const *s1, const char *s2);
extern char *ft_strcpy(char *dst, char const *src);
extern ssize_t ft_write(int fd, const void *buf, size_t nbyte);
extern ssize_t ft_read(int fd, void *buf, size_t nbyte);
extern char *ft_strdup(char const *s1);


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

    printf("Test: ==> ft_strlen\n");
    STRLEN("");
    STRLEN("abcd");
    STRLEN("ABCDEFG");
    STRLEN("0123456789abcdef");
    STRLEN("42");
    STRLEN("1");
    printf("Test OK\n");

    printf("\nTest: ==> ft_strcmp\n");
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

    printf("\nTest: ==> ft_strcpy\n");
    printf("`%s` (`abcd`)\n", ft_strcpy(buffer, "abcd"));
	printf("`%s` (empty)\n", ft_strcpy(buffer, ""));
	printf("`%s` (`long message`)\n", ft_strcpy(buffer, "long message"));
	// printf("`%s` (NULL > not modified)\n", ft_strcpy(buffer, NULL));
    printf("Test OK\n");

    printf("\nTest: ==> ft_write\n");
	WRITE("abcd", 4L);
	WRITE("abcdabcd", 4L);
	WRITE("abcdabcd", 8L);
	WRITE("abcd", 2L);
	printf("Test OK\n");

    printf("\nTest: ==> ft_read (Makefile)\n");
	printf("Por favor, introduce algo para el test de read (máx 50 chars):\n");
    READ(buffer, 50);
    printf("Por favor, introduce algo para el test de read (máx 25 chars):\n");
    READ(buffer, 25);
    printf("Por favor, introduce algo para el test de read (máx 4 chars):\n");
    READ(buffer, 4);
    printf("Por favor, introduce algo para el test de read (máx 26 chars):\n");
    READ(buffer, 26);
    printf("Por favor, introduce algo para el test de read (máx 14 chars):\n");
    READ(buffer, 14);
    printf("Test de lectura de 0 bytes:\n");
    READ(buffer, 0);
    printf("Test OK\n");

    printf("\nTest: ==> ft_strdup\n");
	aux2 = ft_strdup("abcd");
	STRDUP(aux2);
    free(aux2);
	STRDUP("tester");
	STRDUP("long message");
	STRDUP("");
	// STRDUP(NULL);
	printf("Test OK\n");
        

    printf("--------------------------------------------------\n");
    printf("Todas las pruebas automáticas comparando el original están OK!\n");

    return 0;
}
