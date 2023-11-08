section .text
    global _start

_exit:
    mov ebx, 60
    mov eax, 1
    int 0x80

_start:
    push byte 0
    call _exit
