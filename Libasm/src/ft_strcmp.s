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
    xor     rax, rax

.loop:
    cmp     BYTE [rdi], 0
    je      .calculate
    cmp     BYTE [rsi], 0
    je      .calculate

    cmp     BYTE [rdi], BYTE [rsi]
    jne     calculate

    inc     rdi
    inc     rsi
    jmp     .loop

.calculate:
    mov     al, BYTE [rdi]
    mov     bl, BYTE [rsi]
    sub     al, bl
    mov     rax, al
    jmp     .end_loop  

.end_loop:
    ret