	.section	__TEXT,__text,regular,pure_instructions
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp2:
	.cfi_def_cfa_offset 16
Ltmp3:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp4:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	leaq	L_.str(%rip), %rax
	leaq	-20(%rbp), %rcx
	movl	$0, -4(%rbp)
	movl	%edi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rax, %rdi
	movq	%rcx, %rsi
	movb	$0, %al
	callq	_scanf
	movl	$0, -24(%rbp)
	movl	%eax, -28(%rbp)         ## 4-byte Spill
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	movl	-24(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jge	LBB0_4
## BB#2:                                ##   in Loop: Header=BB0_1 Depth=1
	callq	__Z3runv
	leaq	L_.str1(%rip), %rdi
	movl	%eax, %esi
	movb	$0, %al
	callq	_printf
	movl	%eax, -32(%rbp)         ## 4-byte Spill
## BB#3:                                ##   in Loop: Header=BB0_1 Depth=1
	movl	-24(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -24(%rbp)
	jmp	LBB0_1
LBB0_4:
	movl	$0, %eax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.globl	__Z3runv
	.align	4, 0x90
__Z3runv:                               ## @_Z3runv
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp7:
	.cfi_def_cfa_offset 16
Ltmp8:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp9:
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	leaq	L_.str(%rip), %rdi
	leaq	-8(%rbp), %rsi
	movb	$0, %al
	callq	_scanf
	leaq	L_.str2(%rip), %rdi
	leaq	-12(%rbp), %rsi
	leaq	-16(%rbp), %rdx
	movl	%eax, -32(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_scanf
	movl	-12(%rbp), %ecx
	cmpl	-16(%rbp), %ecx
	movl	%eax, -36(%rbp)         ## 4-byte Spill
	jne	LBB1_8
## BB#1:
	movl	$2, -24(%rbp)
LBB1_2:                                 ## =>This Inner Loop Header: Depth=1
	movl	-24(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jge	LBB1_7
## BB#3:                                ##   in Loop: Header=BB1_2 Depth=1
	leaq	L_.str(%rip), %rdi
	leaq	-20(%rbp), %rsi
	movb	$0, %al
	callq	_scanf
	movl	-20(%rbp), %ecx
	cmpl	-12(%rbp), %ecx
	movl	%eax, -40(%rbp)         ## 4-byte Spill
	je	LBB1_5
## BB#4:
	movl	-24(%rbp), %eax
	movl	%eax, -4(%rbp)
	jmp	LBB1_15
LBB1_5:                                 ##   in Loop: Header=BB1_2 Depth=1
	jmp	LBB1_6
LBB1_6:                                 ##   in Loop: Header=BB1_2 Depth=1
	movl	-24(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -24(%rbp)
	jmp	LBB1_2
LBB1_7:
	jmp	LBB1_14
LBB1_8:
	movl	$2, -28(%rbp)
## BB#9:
	movl	-28(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jge	LBB1_13
## BB#10:
	leaq	L_.str(%rip), %rdi
	leaq	-20(%rbp), %rsi
	movb	$0, %al
	callq	_scanf
	movl	-20(%rbp), %ecx
	cmpl	-12(%rbp), %ecx
	movl	%eax, -44(%rbp)         ## 4-byte Spill
	jne	LBB1_12
## BB#11:
	movl	$2, -4(%rbp)
	jmp	LBB1_15
LBB1_12:
	movl	$1, -4(%rbp)
	jmp	LBB1_15
LBB1_13:
	jmp	LBB1_14
LBB1_14:
	movl	$0, -4(%rbp)
LBB1_15:
	movl	-4(%rbp), %eax
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"%d"

L_.str1:                                ## @.str1
	.asciz	"%d\n"

L_.str2:                                ## @.str2
	.asciz	"%d %d"


.subsections_via_symbols
