; -----------------------------------------------------------------------------
; -----------------------------------------------------------------------------
; ft_strcmp:
;   Compara las cadenas carácter por carácter (lexicográficamente)
;   hasta que encuentra el primer carácter diferente o hasta que llega al
;   terminador nulo de cualquiera de las dos cadenas.
;
; Argumentos:
;   RDI - Puntero a la cadena de caracteres (const char *s1)
;   RSI - Puntero a la cadena de caracteres (const char *s2)
;
; Retorno:
;   RAX - La igualdad o difencia lexicográfica entre las cadenas (int)
; -----------------------------------------------------------------------------
; -----------------------------------------------------------------------------

section .text
global _ft_strcmp

_ft_strcmp:
	xor		rax, rax	

.loop:
	mov		r8b, BYTE[rdi]      ; Uso el registro de Propósito genral de 8bits
	mov		r9b, BYTE[rsi]      ; Uso el registro de Propósito genral de 8bits
	
	cmp		BYTE[rdi], 0
	je		.calculate
	cmp		BYTE[rsi], 0
	je		.calculate
	
	
	cmp		r9b, r8b
	jne		.calculate

	inc		rdi
	inc		rsi
	
	jmp		.loop

.calculate:
	mov		al, r8b;
	sub		al, r9b
	movsx	rax, al             ; Para extender correctamente el resultado de la resta con signo a 64 bits, ya que strcmp puede devolver valores negativos.
	jmp		.end_loop

.end_loop:
	ret