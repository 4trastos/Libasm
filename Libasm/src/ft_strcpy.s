; -----------------------------------------------------------------------------
; __ft_strcpy:
;   Copia una cadena de caracteres terminada en nulo.
;
; Argumentos:
;   RDI - Puntero a la cadeda de destino (char *dst)
;   RSI - Puntero a la cadena de origen (const char *src)
;
; Retorno:
;   RAX - Puntero a la cadeda de destino (char *dst)
; -----------------------------------------------------------------------------

section .text
global __ft_strcpy

__ft_strcpy:
	xor		rax, rax
	mov		rax, rdi

.loop:
	cmp		BYTE [rsi], 0
	mov		BYTE [rdi], BYTE [rsi]
	je		.end_loop

	inc		rdi
	inc		rsi

	jmp		.loop

.end_loop:
	ret

