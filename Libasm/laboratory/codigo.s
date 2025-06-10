section .text
    global _start

square:
    push    rbp
    mov     rbp, rsp
    sub     rsp, 16
    mov     [rbp-4], edi
    mov     eax, [rbp-4]
    imul    eax, eax
    mov     rsp, rbp
    pop     rbp
    ret

main:
    push    rbp
    mov     rbp, rsp
    mov     edi, 10
    call    square
    mov     eax, 0
    mov     rsp, rbp
    pop     rbp
    ret

_start:
    call    main

    mov     rax, 0x2000001
    xor     rdi, rdi
    syscall

