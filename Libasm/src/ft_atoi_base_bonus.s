; -----------------------------------------------------------------------------
; -----------------------------------------------------------------------------
; ft_atoi_base:
;   Convierte una cadena de caracteres (char *str) que representa un número
;   en una base dada (char *base_str) a su valor entero (int).
; La función:
;   - Omite cualquier espacio en blanco inicial (' ', '\t', '\n', '\r', '\f', '\v').
;   - Maneja signos opcionales ('+' o '-'). Múltiples signos invierten el signo.
;   - Valida la cadena 'base_str':
;     - Debe contener al menos 2 caracteres.
;     - No debe contener caracteres duplicados.
;     - No debe contener espacios en blanco, '+' o '-'.
;     - Si 'base_str' es inválida o nula, retorna 0.
;   - Convierte los dígitos de 'str' utilizando los caracteres definidos en 'base_str'.
;     - Para bases mayores de 10 (ej. hexadecimal), es insensible a mayúsculas/minúsculas
;       para los dígitos de 'A' a 'F' (asumiendo que 'base_str' usa 'a' a 'f').
;   - La conversión se detiene en el primer carácter de 'str' que no es un dígito
;     válido en la 'base_str' proporcionada.
;   - Si 'str' es nula o no contiene dígitos válidos después de los espacios/signos, retorna 0.
;
; Argumentos (Convención System V AMD64 para macOS/Linux):
;   RDI - Puntero a la cadena de caracteres a convertir (char *str)
;   RSI - Puntero a la cadena que define los dígitos de la base (char *base_str)
;
; Retorno:
;   RAX - El entero convertido (int).
; -----------------------------------------------------------------------------
; -----------------------------------------------------------------------------

section .text
global  _ft_atoi_base

_ft_atoi_base: