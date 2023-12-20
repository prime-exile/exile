GLOBAL exMemset

section .text

[bits 64]
exMemset:
	push rbp
	mov rbp, rsp
	mov eax, 55
	pop rbp
	ret
	