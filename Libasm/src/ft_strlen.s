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
    xor     rax, rax        ; Establece RAX a 0 (nuestro contador de longitud)

.loop:
    cmp     BYTE [rdi], 0   ; Compara el byte actual apuntado por RDI con 0
    je      .end_loop       ; Si es 0, hemos encontrado el final de la cadena

    inc     rax             ; Incrementar el contador de longitud
    inc     rdi             ; Mover el puntero a la siguiente posición

    jmp     .loop           ; Volver a la etiqueta .loop

.end_loop:
    ret                     ; Retornar de la función (RAX ya tiene la longitud)
