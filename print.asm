bits 64

global _start

section .text

_start:
  mov eax, 1        ; write(
  mov edi, 1        ;   STDOUT_FILENO,
  lea rsi, [rel msg]      ;   "Hello, world!\n",
  mov rdx, msglen   ;   sizeof("Hello, world!\n")
  syscall           ; );

  xor edi, edi
  xor rsi, rsi
  xor rdx, rdx
  lea rax, [rel _start]
  sub rax, 0x41414141
  jmp rax

;   mov rax, 60       ; exit(
;   mov rdi, 0        ;   EXIT_SUCCESS
;   syscall           ; );

section .rodata0
  msg: db "....WOODY....", 10
  msglen: equ $ - msg