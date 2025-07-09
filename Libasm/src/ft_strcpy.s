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
global _ft_strcpy

_ft_strcpy:
	xor		rax, rax			
	mov		rbx, rdi			; Guardo el puntero original de destino

.loop:
	mov		r8b, BYTE [rsi]		
	mov		BYTE [rdi], r8b

	cmp		r8b, 0				
	je		.end_loop

	inc		rsi					
	inc		rdi					

	jmp		.loop				

.end_loop:
	mov		rax, rbx			; Devuelvo el puntero original
	ret