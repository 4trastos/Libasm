; -----------------------------------------------------------------------------------------
; -----------------------------------------------------------------------------------------
; ft_write:
;   write() intenta escribir (nbyte) bytes de datos desde el búfer (buf) hacia el
;   objeto referenciado por el descriptor (fildes).
;
; Argumentos:
;   RDI - Regitro del periférico / objeto referenciado (int fildes)
;   RSI - Puntero a la cadena de caracteres (const void *buf)
;   RDX - Registro del número de bytes a enviar (size_t nbyte)
;
; Retorno:
;   RAX - Registro del número de bytes enviado al periférico / objeto referenciado (ssize_t)
; ------------------------------------------------------------------------------------------
; ------------------------------------------------------------------------------------------

section .text
global _ft_write

extern ___error                     ; Función externa que devuelve la dirección de la variable errno

_ft_write:
    mov     rax, 0x2000004          ; Se carga el número de syscall para 'write' en RAX (man 2 syscall)

    syscall                         ; Ejecuta la llamada al sistema. Esta instrucción transfiere el control al kernel.

    cmp     rax, 0                  ; Compara el valor de retorno con 0
    jc      .handle_error           ; Si el Carry Flag (CF) está establecido (indicando un error),

    ret                             ; Retorna el valor en RAX

.handle_error:
    push    rax                     ; Guarda el código de error positivo (actualmente en RAX) en el Stack (RAM) temporalmente.
    call    ___error                ; Llama a la función que devuelve la dirección de 'errno'.
    pop     rdi                     ; Recupera el código de error positivo original de el Stack (RAM).
    mov     [rax], rdi              ; Mueve el código de error (que está en RDI) a la dirección de 'errno'
    mov     rax, -1                 ; Establece el valor de retorno final de ft_write a -1,

    ret