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

extern size_t _ft_strlen(const char *s);
extern char *_ft_strcpy( char *dst, const char *src);

int main() {
    const char *str1 = "Hola Mundo";
    const char *str2 = "";
    const char *str3 = "12345";
    const char *str4 = "a";
    size_t original_len;
    size_t my_len;

    printf("Probando ft_strlen y comparando con strlen original:\n");
    printf("--------------------------------------------------\n");

    // Prueba 1
    my_len = _ft_strlen(str1);
    original_len = strlen(str1);
    printf("Cadena: '%s'\n", str1);
    printf("  ft_strlen: %zu\n", my_len);
    printf("  strlen:    %zu\n", original_len);
    assert(my_len == original_len); // Mantenemos el assert para la verificación de errores
    printf("  Resultado: %s\n\n", (my_len == original_len) ? "COINCIDE" : "NO COINCIDE");


    // Prueba 2
    my_len = _ft_strlen(str2);
    original_len = strlen(str2);
    printf("Cadena: '%s'\n", str2);
    printf("  ft_strlen: %zu\n", my_len);
    printf("  strlen:    %zu\n", original_len);
    assert(my_len == original_len);
    printf("  Resultado: %s\n\n", (my_len == original_len) ? "COINCIDE" : "NO COINCIDE");


    // Prueba 3
    my_len = _ft_strlen(str3);
    original_len = strlen(str3);
    printf("Cadena: '%s'\n", str3);
    printf("  ft_strlen: %zu\n", my_len);
    printf("  strlen:    %zu\n", original_len);
    assert(my_len == original_len);
    printf("  Resultado: %s\n\n", (my_len == original_len) ? "COINCIDE" : "NO COINCIDE");


    // Prueba 4
    my_len = _ft_strlen(str4);
    original_len = strlen(str4);
    printf("Cadena: '%s'\n", str4);
    printf("  ft_strlen: %zu\n", my_len);
    printf("  strlen:    %zu\n", original_len);
    assert(my_len == original_len);
    printf("  Resultado: %s\n\n", (my_len == original_len) ? "COINCIDE" : "NO COINCIDE");


    printf("--------------------------------------------------\n");
    printf("Todas las pruebas automáticas comparando el original están OK!\n");

    return 0;
}
