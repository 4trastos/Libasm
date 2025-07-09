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
global  _ft_read

extern __errno_location                     ; Función externa que devuelve la dirección de la variable errno

_ft_read:
    mov     rax, 0                          ; Se carga el número de syscall para 'read' en RAX (man 2 syscall) 
    syscall                                 ; Ejecuta la llamada al sistema. Esta instrucción transfiere el control al kernel.

    cmp     rax, 0
    jl      .handle_error                   ; Salta si es negativo (error)

    ret

.handle_error:
    neg     rax                             ; Convierte el error negativo a positivo
    push    rax                             ; Guarda el código de error
    call     __errno_location wrt ..plt     ; Llama a la función que devuelve la dirección de errno
    pop     rdx
    mov     [rax], rdx                      ; almacenar el código de errno
    mov     rax, -1                         ; Establece el valor de retorno final de ft_read a -1,

    ret

