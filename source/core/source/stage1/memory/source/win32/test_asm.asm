; wont forget about _ before function name
GLOBAL _example_bl

section .text

[bits 32]
_example_bl:
	push ebp
	mov eax, 55
	pop ebp
	ret
	