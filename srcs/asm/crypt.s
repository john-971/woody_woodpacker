
section .text
global	cipher


cipher:

	push rbp
	mov rbp, rsp
	sub rsp, 288
	mov QWORD [rsp], rdi 			;save for param input pointer
	mov QWORD [rsp + 8], rsi		;save for param key pointer
	mov QWORD [rsp + 16], rdx		;save for param input_len
	mov DWORD [rsp + 24], -1		;i = -1
	mov DWORD [rsp + 28], 0			;j = 0
									;rsp + 32 = tab
	jmp .init

.init:								;Create tab[255] = 0,1,2,3...255
	mov eax, DWORD [rsp + 24]
	cmp eax, 255
	jge .shuffle
	add eax, 1
	mov DWORD [rsp + 24], eax
	mov edx, eax
	cdqe							;sign eax and put it to rax for address alignement
	mov BYTE [rsp + 32 + rax], dl	;dl is juste a byte register that contain 'i'

	lea rsi, [rsp + 32 + rax]	  	;pointer to print
	mov eax, 1        				; write(
	mov edi, 1        				;   STDOUT_FILENO,
	; lea rsi, [rdi]      			;   "Hello, world!\n",
	mov rdx, 1   					;   sizeof("Hello, world!\n")
	syscall           				; );

	jmp .init

.shuffle:

	mov DWORD [rsp + 24], -1		; i = -1
	mov eax, DWORD [rsp + 24]		; i
	cmp eax, 255
	jge .keystream
	add eax, 1
	mov DWORD [rsp + 24], eax		; i += 1;
	cdqe							; double to quad word
	movzx eax, BYTE [rsp + 32 + rax]; tab[i]

	mov edi, DWORD [rsp + 28]		; j
	add edi, eax					; j + tab[i]

	mov eax, DWORD [rsp + 24]		; i
	cdqe
	and eax, 15						; i & 15
	mov rcx, rax					; i & 15
	mov QWORD rax, [rsp + 8]		; pointer key
	add rax, rcx					; pointer key[i & 15]
	movzx eax, BYTE [rax]			; pointer key[i & 15]
	add eax, edi					; j + tab[i] + pointer key[i & 15]
	and eax, 255					;( j + tab[i] + pointer key[i & 15]) & 255
	mov DWORD [rsp + 28], eax		;j = ( j + tab[i] + pointer key[i & 15]) & 255
	jmp .swap

.swap:

	mov eax, DWORD [rsp + 24]		; i;
	cdqe							; double to quad word
	movzx eax, BYTE [rsp + 32 + rax]; tab[i]
	mov edi, eax					; edi = tab[i]

	mov eax, DWORD [rsp + 28]		; j;
	cdqe							; double to quad word
	movzx eax, BYTE [rsp + 32 + rax]; tab[j]
	mov esi, eax					; esi = tab[j]
	xor edi, esi					; edi = tab[i] ^ tab[j]
	xor esi, edi					; esi = tab[j] ^ edi
	xor edi, esi					; edi = edi ^ esi
	
	mov eax, DWORD [rsp + 28]		; j
	mov edx, esi
	cdqe
	mov BYTE [rsp + 32 + rax], dl	; tab[j] = esi


	mov eax, DWORD [rsp + 24]		; i
	mov edx, edi
	cdqe
	mov BYTE [rsp + 32 + rax], dl; tab[i] = edi

	jmp .shuffle + 8


	; mov rsi, [rsp]	  ;pointer to print
	; mov eax, 1        ; write(
	; mov edi, 1        ;   STDOUT_FILENO,
	; ; lea rsi, [rdi]      ;   "Hello, world!\n",
	; mov rdx, 8   	;   sizeof("Hello, world!\n")
	; syscall           ; );

.keystream:

	lea rsi, [rsp + 32]	  ;pointer to print
	mov eax, 1        ; write(
	mov edi, 1        ;   STDOUT_FILENO,
	; lea rsi, [rdi]      ;   "Hello, world!\n",
	mov rdx, 255   	;   sizeof("Hello, world!\n")
	syscall           ; );

	jmp .end

.end:
	mov rax, 60       ; exit(
	mov rdi, 0        ;   EXIT_SUCCESS
	syscall           ; );