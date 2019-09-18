bits 64

global _start

; section .text

_start:

	xor edi, edi
	xor rsi, rsi
	xor rdx, rdx
	xor rax, rax
	jmp boucle

_boucle
	cmp rdx, 0x43434343		;len
  	ja fin
	lea rax, [rel _start]
  	sub rax, 0x42424242		;diff
	add rax, rdx

	xor [rax], 
	  
  
  jmp _start

_fin:
	xor edi, edi
	xor rsi, rsi
	xor rdx, rdx
	lea rax, [rel _start]
	sub rax, 0x41414141
	jmp rax
;   mov rax, 60       ; exit(
;   mov rdi, 0        ;   EXIT_SUCCESS
;   syscall           ; );

; section .rodata0
  msg: db "ZZZZZ", 0
  msglen: equ $ - msg