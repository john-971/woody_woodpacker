
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
	mov DWORD [rsp + 28], -1		;j = -1
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

	lea rsi, [rsp + 32 + rax]	  ;pointer to print
	mov eax, 1        ; write(
	mov edi, 1        ;   STDOUT_FILENO,
	; lea rsi, [rdi]      ;   "Hello, world!\n",
	mov rdx, 1   	;   sizeof("Hello, world!\n")
	syscall           ; );

	jmp .init

.shuffle:
	jmp .end
	
	; mov rsi, [rsp]	  ;pointer to print
	; mov eax, 1        ; write(
	; mov edi, 1        ;   STDOUT_FILENO,
	; ; lea rsi, [rdi]      ;   "Hello, world!\n",
	; mov rdx, 8   	;   sizeof("Hello, world!\n")
	; syscall           ; );

.end:
	mov rax, 60       ; exit(
	mov rdi, 0        ;   EXIT_SUCCESS
	syscall           ; );