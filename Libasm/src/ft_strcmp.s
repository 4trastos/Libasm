; -----------------------------------------------------------------------------
; -----------------------------------------------------------------------------
; __ft_strcmp:
;   Compara las cadenas carácter por carácter (lexicográficamente)
;   hasta que encuentra el primer carácter diferente o hasta que llega al
;   terminador nulo de cualquiera de las dos cadenas.
;
; Argumentos:
;   RDI - Puntero a la cadena de caracteres (const char *s1)
;   RSI - Puntero a la cadena de caracteres (const char *s2)
;
; Retorno:
;   RAX - La igualdad o difencia lexicográfica entre las cadenas (int)
; -----------------------------------------------------------------------------
; -----------------------------------------------------------------------------

section .text
global __ft_strcmp

__ft_strcmp:
    xor     rax, rax                    ; Inicializa el registro de retorno

.loop:
    cmp     BYTE [rdi], 0               ; ¿s1[i] es NULL?
    je      .calculate                  ; Si sí, salta a calcular el resultado final
    cmp     BYTE [rsi], 0
    je      .calculate

    cmp     BYTE [rdi], BYTE [rsi]      ; Compara los caracteres s1[i] y s2[i]
    jne     calculate                   ; Si son diferentes, salta a calcular el resultado final

    inc     rdi                         ; Avanza el puntero de s1
    inc     rsi                         ; Avanza el puntero de s2
    jmp     .loop                       ; Continúa el bucle

.calculate:
    mov     al, BYTE [rdi]              ; Carga s1[i] en AL
    mov     bl, BYTE [rsi]              ; Carga s2[i] en BL
    sub     al, bl                      ; Calcula la diferencia (s1[i] - s2[i])
    mov     rax, al                     ; Mueve el resultado a RAX (extendiendo el signo)
    jmp     .end_loop                   ; Salta al final para retornar

.end_loop:
    ret