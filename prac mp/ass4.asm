;Finding the greatest number in the block

section .data
block: dq 0x0111111123454323, 0xFAB3213298765443, 0x01FAC32156765456, 0x0435253564323456, 0xA123123123122134
greatest: dq 0x0000000000000000
cnt: db 0x00

str1: db "The greatest number is: ",0xA
len1: equ $- str1


section .bss
result: resb 20

section .text
global _start

_start:
	
	mov rsi, block
	mov rcx, 0x5
	
	;Checking if the current number is greater than greatest number defined or not
	checking:
	mov rax, qword[rsi]
	cmp rax, qword[greatest]
	jbe next			;If number is less than greatest go to the next element
	mov qword[greatest], rax	;This indicates number is greater and it is moved to greatest
	
	next:
	add rsi, 8
	dec rcx
	jnz checking		;For checking all elements of the block
	
	;Converting hex number to ascii number
	
	mov rax, qword[greatest]
	mov byte[cnt], 16
	mov rsi, result
	
	
	l1:
		rol rax, 4
		mov bl , al
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
	
	mov rax, 1
	mov rdi, 1
	mov rsi, str1
	mov rdx, len1
	syscall
	
	mov rax, 1
	mov rdi, 1
	mov rsi, result
	mov rdx, 20
	syscall
	
	
	mov rax, 60
	mov rdi, 00
	syscall