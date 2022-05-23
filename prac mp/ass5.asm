;Doing arithmetic operations

section .data
cnt: db 0x00
num1: dq 0x0000000000000004
num2: dq 0x0000000000000002

menut db "1. ADDITION 2.SUBSTRACTION 3.MULTIPLICATION 4. DIVISION 5.EXIT"
menul: equ $- menut


str7: db "", 0xA
len7: equ $- str7

str1: db "Enter your choice: ", 0xA
len1: equ $- str1

str2: db "2", 0xA
len2: equ $- str2


section .bss
result: resb 20
choice: resb 20

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
	
	menu:
	print menut, menul
	print str7, len7
	print str1, len1
	
	mov rax, 0
	mov rdi, 0
	mov rsi, choice
	mov rdx, 2
	syscall
	
	
	cmp byte[choice], 31h
	je label1
		
	cmp byte[choice], 32h
	je label2
	
	cmp byte[choice], 33h
	je label3
	
	label1: 
		call addition
		jmp menu
	
	addition:
		mov rax, [num1]
		mov rbx, [num2]
		add rax, rbx
		mov rsi, result
		call con
		print result, 16
		print str7, len7
		ret
	
	label2:
		call subtraction
		jmp menu 	
	
	subtraction:
		mov rax, [num1]
		mov rbx, [num2]
		sub rax, rbx
		mov rsi, result
		call con
		print result, 16
		print str7, len7
		ret
		
	label3:
		call division
		print str7, 16
		jmp menu
	
	division:
		xor rax, rax
	xor rdx, rdx
	mov rax, qword[num1]
	div qword[num2]
	mov rsi, DivisionResult
	CALL HexToASCII
	IO 01, 01, DivisionResult, 16
	IO 01, 01, newLine, len
	ret
	

    label4:
        call Multiplication
        jmp menu
        
	Multiplication:
	xor rax, rax
	xor rdx, rdx
	mov rax, qword[num1]
	mul qword[num2]
	push rax
	mov rax, rdx
	mov rsi, MultiplicationResult
	CALL HexToASCII
	pop rax
	CALL HexToASCII
	IO 01,01, MultiplicationResult, 32
	IO 01, 01, newLine, len
	ret

	
	mov rax, 60
	mov rdi, 00
	syscall

        
	con: 	
		mov byte[cnt], 16
		
		
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
		ret