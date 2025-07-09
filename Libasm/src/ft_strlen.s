; -----------------------------------------------------------------------------
; -----------------------------------------------------------------------------
; t_strlen:
;   Calcula la longitud de una cadena de caracteres terminada en nulo.
;
; Argumentos:
;   RDI - Puntero a la cadena de caracteres (char *s)
;
; Retorno:
;   RAX - La longitud de la cadena (size_t)
; -----------------------------------------------------------------------------
; -----------------------------------------------------------------------------

section .text
global _ft_strlen

_ft_strlen:
    xor     rax, rax

.loop:
    cmp     BYTE[rdi], 0
    je      .end_loop

    inc     rax
    inc     rdi

    jmp     .loop

.end_loop:
    ret
