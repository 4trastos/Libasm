section .text
global  _ft_atoi_base

_ft_atoi_base:
    push    rbp
    mov     rbp, rsp
    push    rbx
    push    r12
    push    r13
    push    r14
    push    r15

    ; Validar inputs
    test    rdi, rdi
    jz      .error_exit
    test    rsi, rsi
    jz      .error_exit

    ; Guardar punteros originales
    mov     r12, rdi        ; r12 = str
    mov     r13, rsi        ; r13 = base_str

    ; Validar la base
    mov     rdi, r13
    call    .ft_get_base_value
    test    rax, rax
    jz      .error_exit
    mov     r14, rax        ; r14 = base_len

    ; Saltar espacios blancos
    mov     rdi, r12
    call    .skip_whitespace
    mov     r12, rax        ; actualizar str pointer

    ; Manejar signos
    call    .handle_sign
    mov     r15d, eax       ; r15d = sign

    ; Convertir el número
    xor     eax, eax        ; result = 0
    .conversion_loop:
        movzx   edi, byte [r12]
        test    dil, dil
        jz      .conversion_done

        ; Obtener valor del dígito
        mov     rsi, r13
        mov     edx, r14d
        call    .ft_get_digit_value
        cmp     eax, -1
        je      .conversion_done

        ; Actualizar resultado: result = result * base + digit
        imul    eax, r14d
        add     eax, edx

        inc     r12
        jmp     .conversion_loop

    .conversion_done:
        ; Aplicar signo
        imul    eax, r15d
        jmp     .exit

.error_exit:
    xor     eax, eax

.exit:
    pop     r15
    pop     r14
    pop     r13
    pop     r12
    pop     rbx
    pop     rbp
    ret

; ==============================================
; Subrutinas
; ==============================================

.ft_get_base_value:
    push    rbp
    mov     rbp, rsp
    push    rbx
    push    r12
    push    r13

    mov     r12, rdi        ; guardar base_str

    ; Verificar base_str no nula
    test    r12, r12
    jz      .invalid_base

    ; Calcular longitud y verificar caracteres prohibidos
    xor     rbx, rbx        ; contador de longitud
    .length_loop:
        mov     al, byte [r12 + rbx]
        test    al, al
        jz      .length_done

        ; Verificar caracteres prohibidos
        call    .is_forbidden_char
        test    al, al
        jnz     .invalid_base

        inc     rbx
        jmp     .length_loop

    .length_done:
        ; Verificar longitud mínima
        cmp     rbx, 2
        jl      .invalid_base

        ; Verificar duplicados
        mov     rdi, r12
        mov     rsi, rbx
        call    .has_duplicates
        test    al, al
        jnz     .invalid_base

        ; Base válida, retornar longitud
        mov     rax, rbx
        jmp     .base_valid

    .invalid_base:
        xor     rax, rax

    .base_valid:
        pop     r13
        pop     r12
        pop     rbx
        pop     rbp
        ret

.is_forbidden_char:
    cmp     al, ' '
    je      .forbidden
    cmp     al, 9           ; \t
    je      .forbidden
    cmp     al, 10          ; \n
    je      .forbidden
    cmp     al, 13          ; \r
    je      .forbidden
    cmp     al, 12          ; \f
    je      .forbidden
    cmp     al, 11          ; \v
    je      .forbidden
    cmp     al, '+'
    je      .forbidden
    cmp     al, '-'
    je      .forbidden
    xor     al, al
    ret
    .forbidden:
    mov     al, 1
    ret

.has_duplicates:
    push    rbp
    mov     rbp, rsp
    push    rbx
    push    r12
    push    r13

    mov     r12, rdi        ; base_str
    mov     r13, rsi        ; length

    xor     rbx, rbx        ; i = 0
    .outer_loop:
        cmp     rbx, r13
        jge     .no_duplicates

        mov     al, byte [r12 + rbx]
        mov     rcx, rbx
        inc     rcx         ; j = i + 1
        .inner_loop:
            cmp     rcx, r13
            jge     .inner_done

            mov     dl, byte [r12 + rcx]
            cmp     al, dl
            je      .duplicate_found

            inc     rcx
            jmp     .inner_loop

        .inner_done:
            inc     rbx
            jmp     .outer_loop

    .duplicate_found:
        mov     al, 1
        jmp     .exit_duplicates

    .no_duplicates:
        xor     al, al

    .exit_duplicates:
        pop     r13
        pop     r12
        pop     rbx
        pop     rbp
        ret

.skip_whitespace:
    .skip_loop:
        mov     al, byte [rdi]
        cmp     al, ' '
        je      .skip_char
        cmp     al, 9       ; \t
        je      .skip_char
        cmp     al, 10      ; \n
        je      .skip_char
        cmp     al, 13      ; \r
        je      .skip_char
        cmp     al, 12      ; \f
        je      .skip_char
        cmp     al, 11      ; \v
        je      .skip_char
        jmp     .skip_done
    .skip_char:
        inc     rdi
        jmp     .skip_loop
    .skip_done:
        mov     rax, rdi
        ret

.handle_sign:
    mov     eax, 1          ; sign = 1
    .sign_loop:
        mov     cl, byte [r12]
        cmp     cl, '-'
        je      .neg_sign
        cmp     cl, '+'
        je      .pos_sign
        jmp     .sign_done
    .neg_sign:
        neg     eax
    .pos_sign:
        inc     r12
        jmp     .sign_loop
    .sign_done:
        ret

.ft_get_digit_value:
    push    rbp
    mov     rbp, rsp
    push    rbx

    mov     eax, edi        ; c
    mov     rbx, rsi        ; base_str
    mov     ecx, edx        ; base_len

    ; Convertir a minúscula si es mayúscula (A-Z)
    cmp     al, 'A'
    jl      .check_digit
    cmp     al, 'Z'
    jg      .check_digit
    add     al, 32          ; convertir a minúscula

.check_digit:
    xor     edx, edx        ; index = 0
    .digit_loop:
        cmp     edx, ecx
        jge     .digit_not_found

        mov     r8b, byte [rbx + rdx]
        cmp     al, r8b
        je      .digit_found

        inc     edx
        jmp     .digit_loop

.digit_found:
    mov     eax, edx        ; return digit value
    jmp     .digit_exit

.digit_not_found:
    mov     eax, -1         ; return -1 (invalid)

.digit_exit:
    pop     rbx
    pop     rbp
    ret