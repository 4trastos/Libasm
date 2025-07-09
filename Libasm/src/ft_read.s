; -----------------------------------------------------------------------------------------
; -----------------------------------------------------------------------------------------
;   ssize_t _ft_read(int fd, void *buf, size_t nbyte); 
;
;ft_read:
;   read() intenta leer nbytes (size_t nbyte) de datos del objeto referenciado por el
;   descriptor fildes (int fd) en el búfer apuntado por (void *buf).
;
; Argumentos:
;   RDI - Regitro del periférico / objeto referenciado (int fd)
;   RSI - Puntero a la cadena de caracteres que va a leer (void *buf)
;   RDX - Registro del número de bytes a leer (size_t nbyte)
;
; Retorno:
;   RAX - Registro del número de bytes leidos al periférico / objeto referenciado (ssize_t)
; ------------------------------------------------------------------------------------------
; ------------------------------------------------------------------------------------------

section .text
global  _ft_read

extern __errno_location                     

_ft_read:
    mov     rax, 0                          
    syscall                                 

    cmp     rax, 0
    jl      .handle_error                  

    ret

.handle_error:
    neg     rax                             
    push    rax                            
    call     __errno_location wrt ..plt     
    pop     rdx
    mov     [rax], rdx                     
    mov     rax, -1                        

    ret

