	.file	"echo.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"!!!You touch the explosion"
	.text
	.globl	explosion
	.type	explosion, @function
explosion:
	subq	$8, %rsp
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %edi
	call	exit
	.size	explosion, .-explosion
	.globl	custom_gets
	.type	custom_gets, @function
custom_gets:
	pushq	%rbp
	pushq	%rbx
	subq	$8, %rsp
	movq	%rdi, %rbp
	movq	%rdi, %rbx
.L4:
	movq	stdin(%rip), %rdi
	call	getc
	cmpl	$-1, %eax
	je	.L10
	cmpl	$10, %eax
	je	.L10
	addq	$1, %rbx
	movb	%al, -1(%rbx)
	jmp	.L4
.L10:
	cmpl	$-1, %eax
	jne	.L11
	movl	$0, %eax
	cmpq	%rbp, %rbx
	je	.L3
.L11:
	movb	$0, (%rbx)
	movq	%rbp, %rax
.L3:
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	ret
	.size	custom_gets, .-custom_gets
	.globl	echo
	.type	echo, @function
echo:
	subq	$24, %rsp
	leaq	8(%rsp), %rdi
	call	custom_gets
	leaq	8(%rsp), %rdi
	call	puts
	addq	$24, %rsp
	ret
	.size	echo, .-echo
	.globl	main
	.type	main, @function
main:
	subq	$8, %rsp
	movl	$0, %eax
	call	echo
	movl	$0, %eax
	addq	$8, %rsp
	ret
	.size	main, .-main
	.ident	"GCC: (GNU) 8.5.0 20210514 (Red Hat 8.5.0-4)"
	.section	.note.GNU-stack,"",@progbits
