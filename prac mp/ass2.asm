;Assignment 2 string length

section .data
str: db "Assignment 2.......", 0xA
len: equ $- str

cnt: db 0

section .bss
result: resw 1
name: resb 1

%macro input 2
mov rax, 0
mov rdi, 0
mov rsi, %1
mov rdx, %2
syscall
%endmacro

%macro print 2
mov rax, 1
mov rdi, 1
mov rsi, %1
mov rdx, %2
syscall
%endmacro

section .text

global _start

_start:

    print str, len
    input name, 17

    dec rax
    mov byte[cnt], 16
    mov rsi, result

    l1:
        rol rax, 4
        mov bl, al
        and bl, 0x0F
        cmp bl, 0x09
        jbe l2
        add bl, 0x07
        l2:
            add bl, 0x30
            mov [rsi], bl
            inc rsi
            dec byte[cnt]
            jnz l1


    print result, 17

    mov rax, 60
    mov rdi, 00
    syscall