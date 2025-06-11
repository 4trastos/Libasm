; -----------------------------------------------------------------------------------------
; -----------------------------------------------------------------------------------------
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
global  __ft_strdup

extern  __ft_strlen
extern  ___error
extern  _malloc

__ft_strdup:
    xor     rax, rax                ; (1) Inicializo RAX a 0. Esto no es estrictamente necesario, pero a mi me gusta.
    call    __ft_strlen             ; (2) Llamo a __ft_strlen. El argumento (s1) ya está en RDI. Retorna la longitud en RAX.
    mov     rbx, rax                ; (3) Guardo la longitud (de RAX) en RBX puesto que en RAX se almacenará el puntero base.
    
    inc     rbx                     ; (4) Incremento RBX la longitud de la reserva en un bit para almacenar el '\0'
    mov     rcx, rdi                ; (5) Guardo el puntero original de S1 (RDI) en RCX para no perder la referencia
    mov     rdi, rbx                ; (6) Guardo en RDI la longitud de la reserva. malloc recibe como argumento a RDI

    call    _malloc                 ; (7) Llamo a Malloc. Retorna el nuevo puntero (o NULL) en RAX. 
    cmp     rax, 0                  ; (8) Comparo el retorno de malloc (en RAX) con 0 (NULL)
    je      .handle_error           ; (9) Si se activa la Flag ZF (RAX es NULL) malloc falló, salta a .handle_error.

    mov     rsi, rax                ; (10) Guardo el puntero base de la memoria asignada (de RAX) en RSI para el final
    mov     rdx, rax                ; (11) Guardo el puntero base de la memoria asignada (de RAX) en RDX para copiar.
    jmp     .loop

.handle_error:
    call    ___error                ; (1) Obtiene la dirección de la variable 'errno' en RAX.
    mov     dword [rax], 12         ; (2) Muevo el valor 12 (ENOMEM) a la DIRECCIÓN de memoria apuntada por RAX. Con 'dword' un Double Word (4 bytes) es el tamaño de un 'int'.
    mov     rax, 0                  ; (3) Pongo 0 en RAX para el retorno

    ret

.loop:
    cmp     BYTE[rcx], 0            ; (1) Comparo el byte actual de s1 (RCX) con '\0'.
    mov     BYTE[rdx], BYTE[rcx]    ; (2) Copio el byte actual de s1 (RCX) a la nueva cadena (RDX).
    je      .end_loop               ; (3) Si la Flag ZF se activa el byte es '\0', termina el bucle. Ya estará copiado el '\0'.

    inc     rcx                     ; (4) Incremento 1 byte en s1
    inc     rdx                     ; (5) Incremento 1 byte en la cadena nueva

    jmp     .loop                   ; (6) Salta al inicio del bucle.

.end_loop:
    mov     rax, rsi                ; (1)  Muevo el puntero base original (guardado en RSI) a RAX para el retorno
    ret
