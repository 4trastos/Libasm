; -----------------------------------------------------------------------------------------
; -----------------------------------------------------------------------------------------
; char *strdup(const char *s);
;
; ft_strdup:
;   strdup() asigna memoria suficiente para una copia de la cadena s1 (const char *s1),
;   realiza la copia y devuelve un puntero a esta.
;   Si no hay memoria disponible, retorna NULL y errno se establece a ENOMEM.
;
; Argumentos:
;   RDI - Puntero a la cadena de caracteres que va a copiar (const char *s1)
;
; Retorno:
;   RAX - Registro de la cadena copiada
; ------------------------------------------------------------------------------------------
; ------------------------------------------------------------------------------------------

section .text
global  _ft_strdup

extern  _ft_strlen
extern  __errno_location
extern  malloc

_ft_strdup:
    push    rbp                             ; Guarda el base pointer actual
    mov     rbp, rsp                        ; Establece el nuevo base pointer al stack pointer actual

    push    r12                             ; s1 original (src)
    push    r13                             ; callee-saved, puntero para escritura (dst)
    push    rsi                             ; callee-saved, puntero base de malloc
    push    rbx                             ; callee-saved, longitud de s1

    mov     r12, rdi                        ; R12 = s1

    xor     rax, rax                        
    call    _ft_strlen                      ; rax = strlen(s1)
    mov     rbx, rax                        
    
    inc     rbx                             ; incluir '\0'
    mov     rdi, rbx                        ; Guardo en RDI la longitud de la reserva. malloc recibe como argumento a RDI

    call    malloc wrt ..plt                ; Llamo a Malloc. Retorna el nuevo puntero (o NULL) en RAX. 
    cmp     rax, 0
    je      .handle_error                   ; Activa ZF (RAX es NULL) si malloc falló (malloc modifica errno).

    mov     rsi, rax                        ; puntero base de la memoria asignada (de RAX) en RSI para el return
    mov     r13, rax                        ; puntero base de la memoria asignada (de RAX) en RDX para copiar.
    jmp     .loop

.handle_error:
    call    __errno_location wrt ..plt      ; Obtengo la dirección de la variable 'errno' en RAX. (RAX = &errno)
    mov     edi, 12                         ; 12 = ENOMEM
    mov     dword [rax], edi                ; dword = double word = 4 bytes = 32 bits. Escribe valor variable 'errno'.
    mov     rax, 0                          ; Pongo 0 en RAX para el retorno (NULL).

    jmp     .restore
    
    ret

.loop:
    mov     al, BYTE[r12]                   ; (parte baja de RAX).
    mov     BYTE[r13], al 
    cmp     al, 0  
    je      .end_loop

    inc     r12 
    inc     r13 

    jmp     .loop      

.restore:
    pop     rbx                             ; Restaurar RBX
    pop     rsi                             ; Restaurar RSI
    pop     r13                             ; Restaurar R13
    pop     r12                             ; Restaurar R12
    pop     rbp                             ; Restaurar RBP

.end_loop:
    mov     rax, rsi                        ; Mover el puntero base original (guardado en RSI) a RAX para el retorno
    jmp     .restore

    ret
