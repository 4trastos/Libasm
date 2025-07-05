; -----------------------------------------------------------------------------
; -----------------------------------------------------------------------------
; ft_strcpy:
;   Copia una cadena de caracteres terminada en nulo.
;
; Argumentos:
;   RDI - Puntero a la cadeda de destino (char *dst)
;   RSI - Puntero a la cadena de origen (const char *src)
;
; Retorno:
;   RAX - Puntero a la cadeda de destino (char *dst)
; -----------------------------------------------------------------------------
; -----------------------------------------------------------------------------

section .text
global ft_strcpy

ft_strcpy:
	xor		rax, rax			; Inicializo el punturo de destino y retorno
	mov		rax, rdi			; Guardo el puntero de inicio de la copia

.loop:
	mov		cl, BYTE [rsi]		; Guardo el byte de src[i] en un registro para poder comparar
	mov		BYTE [rdi], cl		; Comparo los caracteres
	cmp		cl, 0				; Si son iguales o a terminado sale del bucle
	je		.end_loop

	inc		rdi					; Aumento una posición
	inc		rsi					; Auemnto una posición

	jmp		.loop				; Vuelve a iniciar el loop

.end_loop:
	ret