;Checking if numbers are negative or positive 

section .data

block: dq 0x0111111123454323, 0xFAB3213298765443, 0x01FAC32156765456, 0xA435253564323456, 0xA123123123122134

str1: db "The negative numbers are ", 0xA
len1: equ $- str1

str2: db "The positive numbers are ", 0xA
len2: equ $- str2

section .bss
result_pos: resb 20
result_neg: resb 20

section .text
global _start

_start:

	mov rsi, block  ;Moving the block into rsi
 	mov rcx, 0x5	;Moving the number of elements/count into rcx
 	
 	mov rbx, 0	;For counting positive numbers
 	mov rdx, 0 	;For counting negative numbers
 	
 	check:
 		mov rax, [rsi]	;Moving the value of rsi into rax
 		shl rax, 1	;Left shifting the numbers so that the msb becomes a carry
 		jc negative	;If carry is present jump to negative label
 	
 	positive:
 		inc rbx	;increment rbx which stores number of positive values
 		jmp next	;jump to next label
 	
 	negative:
 		inc rdx	;increment rdx which stores number of negative values
 	
 	next:
 		add rsi, 8	;Moving to the element present next in the array
 		dec rcx	;decrementing the count
 		jnz check	;if not zero that is all elements are not checked then jump to check label
 		
 		
 		add dl, 30h		;hexadecimal to ascii conversion for the obtained value
 		mov [result_neg], dl	
 		
 		add bl, 30h		;hexadecimal to ascii conversion for the obtained value
 		mov [result_pos], bl
 		
 		;Printing str2
 		mov rax,1
 		mov rdi,1
 		mov rsi,str2
 		mov rdx,len2
 		syscall
 		
 		;Printing result of positive numbers
 		mov rax,1
 		mov rdi,1
 		mov rsi,result_pos
 		mov rdx,20
 		syscall
 		
 		;Printing str1
 		mov rax,1
 		mov rdi,1
 		mov rsi,str1
 		mov rdx,len1
 		syscall
 		
 		;Printing result of negative numbers
 		mov rax,1
 		mov rdi,1
 		mov rsi,result_neg
 		mov rdx,20
 		syscall
 		
 
	mov rax, 60
	mov rdi, 00
	syscall