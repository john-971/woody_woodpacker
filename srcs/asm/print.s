

section .text
global print_woody
global print_woody_end
global diff

print_woody:
  mov eax, 1        ; write(
  mov edi, 1        ;   STDOUT_FILENO,
  lea rsi, [rel msg]      ;   "Hello, world!\n",
  mov rdx, msglen   ;   sizeof("Hello, world!\n")
  syscall           ; );

  xor edi, edi
  xor rsi, rsi
  xor rdx, rdx
  lea rax, [rel print_woody]
  lea rdx, [rel diff]
  sub rax, rdx
  jmp rax
print_woody_end:


msg: db "....WOODY....", 10
msglen: equ $ - msg
diff: dd 0x42424243


;   mov rax, 60       ; exit(
;   mov rdi, 0        ;   EXIT_SUCCESS
;   syscall           ; );