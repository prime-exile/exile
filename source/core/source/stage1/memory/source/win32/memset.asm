GLOBAL _exMemset

section .text

[bits 32]
_exMemset:
	push ebp
	mov ebp, esp
	mov eax, 55
	pop ebp
	ret
	