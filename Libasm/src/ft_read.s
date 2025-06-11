; -----------------------------------------------------------------------------------------
; -----------------------------------------------------------------------------------------
; ft_read:
;   read() intenta leer nbytes (size_t nbyte) de datos del objeto referenciado por el
;   descriptor fildes (int fildes) en el búfer apuntado por (void *buf).
;
; Argumentos:
;   RDI - Regitro del periférico / objeto referenciado (int fildes)
;   RSI - Puntero a la cadena de caracteres que va a leer (void *buf)
;   RDX - Registro del número de bytes a leer (size_t nbyte)
;
; Retorno:
;   RAX - Registro del número de bytes leidos al periférico / objeto referenciado (ssize_t)
; ------------------------------------------------------------------------------------------
; ------------------------------------------------------------------------------------------

section .text
global  __ft_read

extern ___error                     ; Función externa que devuelve la dirección de la variable errno

__ft_read:
    mov     rax, 0x20000AC          ; Se carga el número de syscall para 'read' en RAX (man 2 syscall)
    
    syscall                         ; Ejecuta la llamada al sistema. Esta instrucción transfiere el control al kernel.

    cmp     rax, 0
    jc      .handle_error

    ret

.handle_error:
    push    rax
    call    ___error
    pop     rsi
    mov     [rax], rsi
    mov     rax, -1

    ret

