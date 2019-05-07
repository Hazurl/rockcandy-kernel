extern kprint
.data
buffer: .word 0, 0
newline: .word '\r', '\n', 0
rax: .word 'r', 'a', 'x', ':', ' ', '0', 'x', 0
rbx: .word 'r', 'b', 'x', ':', ' ', '0', 'x', 0
rcx: .word 'r', 'c', 'x', ':', ' ', '0', 'x', 0
rdx: .word 'r', 'd', 'x', ':', ' ', '0', 'x', 0
.text
.global panic
panic:
	pushq %rcx
	movq rax, %rcx
	pusha
	call kprint
	popa
	popq %rcx
	call putr64
	pushq %rcx
	movq newline, %rcx
	pusha
	call kprint
	movq rbx, %rcx
	call kprint
	popa
	popq %rcx
	movq %rbx, %rax
	call putr64
	pushq %rcx
	movq newline, %rcx
	pusha
	call kprint
	movq rcx, %rcx
	call kprint
	popa
	popq %rcx
	movq %rcx, %rax
	call putr32
	movq newline, %rcx
	pusha
	call kprint
	movq rdx, %rcx
	call kprint
	popa
	movq %rdx, %rax
	call putr64
	movq newline, %rdx
	call kprint
	ret
putr64:
	pushq %rax
	call putr32
	popq %rax
	rorq $32, %rax
	call putr32
	ret
putr32:
	pushl %eax
	call putr16
	popl %eax
	rorl $16, %eax
	call putr16
	ret
putr16:
	pushw %ax
	call putr8
	popw %ax
	rorw $8, %ax
	call putr8
	ret
putr8:
	pushb %al
	call putr4
	popb %al
	rorb $4, %al
	call putr4
	ret
putr4:
	shrb $4, %al
	cmpb $10, %al
	sbbb $105, %al
	das
	pushw %ax
	pushq %rcx
	movq buffer, %rcx
	pusha
	call kprint
	popa
	popq %rcx
	popw %ax
	ret
