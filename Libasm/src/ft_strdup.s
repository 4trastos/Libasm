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

    call    malloc wrt ..plt                ; (7) Llamo a Malloc. Retorna el nuevo puntero (o NULL) en RAX. 
    cmp     rax, 0                          ; (8) Comparo el retorno de malloc (en RAX) con 0 (NULL)
    je      .handle_error                   ; (9) Si se activa la Flag ZF (RAX es NULL) malloc falló, salta a .handle_error.

    mov     rsi, rax                        ; (10) Guardo el puntero base de la memoria asignada (de RAX) en RSI para el final
    mov     r13, rax                        ; (11) Guardo el puntero base de la memoria asignada (de RAX) en RDX para copiar.
    jmp     .loop

.handle_error:
    call    __errno_location wrt ..plt      ; (1) Obtengo la dirección de la variable 'errno' en RAX. (RAX = &errno)
    mov     edi, 12                         ; (2) Mueve el valor 12 (ENOMEM) a ECX (parte baja de RCX).
    mov     dword [rax], edi                ; (3) Muevo el contenido de ECX (12) a la dirección de memoria apuntada por RAX. Escribe valor variable 'errno'.
    mov     rax, 0                          ; (4) Pongo 0 en RAX para el retorno (NULL).

    pop     rbx                             ; Restaurar RBX
    pop     rsi                             ; Restaurar RSI
    pop     r13                             ; Restaurar R13
    pop     r12                             ; Restaurar R12
    pop     rbp                             ; Restaurar RBP
    
    ret

.loop:
    mov     al, BYTE[r12]                   ; (1) Cargo el byte actual de s1 (RCX) en AL (parte baja de RAX).
    mov     BYTE[r13], al                   ; (2) Copio el byte de AL a la nueva cadena (RDX).
    cmp     al, 0                           ; (3) Comparo el byte que acabamos de copiar (en AL) con '\0'.
    je      .end_loop                       ; (4) Si la Flag ZF se activa el byte es '\0', termina el bucle. Ya estará copiado el '\0'.

    inc     r12                             ; (5) Incremento 1 byte en s1
    inc     r13                             ; (6) Incremento 1 byte en la cadena nueva

    jmp     .loop                           ; (7) Salta al inicio del bucle.

.end_loop:
    mov     rax, rsi                        ; (1)  Muevo el puntero base original (guardado en RSI) a RAX para el retorno

    pop     rbx                             ; Restaurar RBX
    pop     rsi                             ; Restaurar RSI
    pop     r13                             ; Restaurar R13
    pop     r12                             ; Restaurar R12
    pop     rbp                             ; Restaurar RBP

    ret
