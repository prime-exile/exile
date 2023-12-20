GLOBAL example_bl

section .text

[bits 64]
example_bl:
	push rbp
	mov eax, 55
	pop rbp
	ret
	