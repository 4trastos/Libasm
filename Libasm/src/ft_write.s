; -----------------------------------------------------------------------------------------
; -----------------------------------------------------------------------------------------
;  ssize_t ft_write(int fd, const void *buf, size_t nbyte);
; ft_write:
;   write() intenta escribir (nbyte) bytes de datos desde el búfer (buf) hacia el
;   objeto referenciado por el descriptor (fd).
;
; Argumentos:
;   RDI - Regitro del periférico / objeto referenciado (int fd)
;   RSI - Puntero a la cadena de caracteres (const void *buf)
;   RDX - Registro del número de bytes a enviar (size_t nbyte)
;
; Retorno:
;   RAX - Registro del número de bytes enviado al periférico / objeto referenciado (ssize_t)
; ------------------------------------------------------------------------------------------
; ------------------------------------------------------------------------------------------

section .text
global  _ft_write

extern __errno_location                     ; Función externa que devuelve la dirección de la variable errno

_ft_write:
    mov     rax, 1                          ; Se carga el número de syscall para 'write' en RAX (man 2 syscall)

    syscall        

    cmp     rax, 0                          
    jl      .handle_error                   ; if rax < 0, jump to error

    ret                                     ; Retorna el valor en RAX

.handle_error:
    neg     rax
    push    rax                             ; Guardo el código de error
    call    __errno_location wrt ..plt      ; llamo a función externa a traves de PLT.
    pop     rdi                             ; Recupera el código de error negativo.
    mov     [rax], rdi                      ; Escribo el valor de errno en la dirección devuelta por __errno_location()
    mov     rax, -1                       

    ret