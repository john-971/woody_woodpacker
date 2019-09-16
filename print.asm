bits 64
; int 0x80
; int 0x80
; mov rdi, 1
; mov rsi, str
; mov rdx, 13
; mov eax, 1
; syscall;

; str: db "....WOODY....";
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

section .rodata
  msg: db "....WOODY....", 10
  msglen: equ $ - msg