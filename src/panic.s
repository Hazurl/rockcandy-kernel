.extern kprint
.data
buffer: .word 0, 0
newline: .word '\r', '\n', 0
rax: .word 'r', 'a', 'x', ':', ' ', '0', 'x', 0
rbx: .word 'r', 'b', 'x', ':', ' ', '0', 'x', 0
rcx: .word 'r', 'c', 'x', ':', ' ', '0', 'x', 0
rdx: .word 'r', 'd', 'x', ':', ' ', '0', 'x', 0
.text
.global panic
pusha:
	pushq %rax
	pushq %rbx
	pushq %rcx
	pushq %rdx
	ret
popa:
	popq %rdx
	popq %rcx
	popq %rbx
	popq %rax
	ret
panic:
	pushq %rcx
	movq rax, %rcx
	call pusha
	call kprint
	call popa
	popq %rcx
	call putr64
	pushq %rcx
	movq newline, %rcx
	call pusha
	call kprint
	movq rbx, %rcx
	call kprint
	call popa
	popq %rcx
	movq %rbx, %rax
	call putr64
	pushq %rcx
	movq newline, %rcx
	call pusha
	call kprint
	movq rcx, %rcx
	call kprint
	call popa
	popq %rcx
	movq %rcx, %rax
	call putr32
	movq newline, %rcx
	call pusha
	call kprint
	movq rdx, %rcx
	call kprint
	call popa
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
	pushq %rax
	call putr16
	popq %rax
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
	pushw %ax
	call putr4
	popw %ax
	rorb $4, %al
	call putr4
	ret
putr4:
	shrb $4, %al
	addb $48, %al
	cmpb $58, %al
	jl putr4.skip
	addb $7, %al
putr4.skip:
	pushw %ax
	pushq %rcx
	movq buffer, %rcx
	call pusha
	call kprint
	call popa
	popq %rcx
	popw %ax
	ret
