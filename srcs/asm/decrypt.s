
section .text
global	decipher
global 	end_decipher


decipher:

	push rbp
	mov rbp, rsp
	sub rsp, 16
	; int 0xcc
	mov DWORD [rsp], -1					; i = -1
	lea rax, [rel decipher]
	movsxd rdx, [rel input_diff]
	sub rax, rdx						; get input pointer
	mov QWORD [rsp + 8], rax			; save input pointer

	mov eax, DWORD [rsp]				; i
	mov ecx, DWORD [rel input_len]		; input_len
	cmp eax, ecx
	jge .exit
	add eax, 1
	mov DWORD [rsp], eax				; i += 1
	mov ecx, eax						; save i
	and eax, 255
	cdqe
	lea rdx, [rel end_decipher]
	movzx edx, BYTE [rdx + rax]			; keystream[i & 255]
	mov rsi, [rsp + 8]					; get input pointer
	mov eax, ecx						; retrieve saved i
	cdqe
	movzx ecx, BYTE [rsi + rax]			; input[i]
	xor ecx, edx
	mov rsi, [rsp + 8]					; input[i] ^ keystream[i & 255]
	mov BYTE [rsi + rax], cl			; input[i] ^= keystream[i & 255]
	jmp decipher + 15
	; jmp decipher + 17 ; + breakpoint

.exit:

	xor edi, edi
	xor rsi, rsi
	xor rdx, rdx
	lea rax, [rel decipher]
	movsxd rdx, [rel woody_diff]
	sub rax, rdx
	xor rdx, rdx
	xor rcx, rcx
	mov	rsp, rbp
	pop	rbp

	jmp rax
	; mov rax, QWORD [rsp]
	; mov	rsp, rbp
	; pop	rbp
	; ret

input_diff:	dd 0x43	; C
input_len: 	dd 0x90 ; Y
woody_diff: dd 0x5a	; Z
end_decipher: