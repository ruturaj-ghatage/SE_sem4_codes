;Take input from user and display it

section .data
str: db "Assignment 1 hehe", 0xA
len: equ $- str

cnt: db 0

section .bss

block : resq 1

%macro print 2
mov rax, 1
mov rdi, 1
mov rsi, %1
mov rdx, %2
syscall
%endmacro

%macro input 2
mov rax, 0
mov rdi, 0
mov rsi, %1
mov rdx, %2
syscall
%endmacro

section .text

global _start
_start:

    print str, len
    mov byte[cnt], 05
    mov rbx, block

    inpute:
        input rbx,17
        add rbx, 17
        dec byte[cnt]
        jnz inpute
    
    mov rbx, block 
    mov byte[cnt], 05

    output:
        print rbx, 17
        add rbx, 17
        dec byte[cnt]
        jnz output

    mov rax, 60
    mov rdi, 00
    syscall