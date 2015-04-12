	.section	__TEXT,__text,regular,pure_instructions
	.globl	__Z11insert_headP5_nodei
	.align	4, 0x90
__Z11insert_headP5_nodei:               ## @_Z11insert_headP5_nodei
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
	movabsq	$16, %rax
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movq	%rax, %rdi
	callq	_malloc
	movq	%rax, -24(%rbp)
	movl	-12(%rbp), %esi
	movq	-24(%rbp), %rax
	movl	%esi, (%rax)
	movq	-8(%rbp), %rax
	movq	-24(%rbp), %rdi
	movq	%rax, 8(%rdi)
	movq	-24(%rbp), %rax
	movq	%rax, -8(%rbp)
	movq	-24(%rbp), %rax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
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
	subq	$16, %rsp
	movl	$0, -4(%rbp)
	movl	%edi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	callq	__Z9unit_testv
	movl	$0, %eax
	addq	$16, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.globl	__Z9unit_testv
	.align	4, 0x90
__Z9unit_testv:                         ## @_Z9unit_testv
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp12:
	.cfi_def_cfa_offset 16
Ltmp13:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp14:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	$0, -16(%rbp)
LBB2_1:                                 ## =>This Inner Loop Header: Depth=1
	leaq	L_.str(%rip), %rdi
	leaq	-4(%rbp), %rsi
	movb	$0, %al
	callq	_scanf
	movb	$1, %cl
	cmpl	$0, %eax
	movb	%cl, -17(%rbp)          ## 1-byte Spill
	jne	LBB2_3
## BB#2:                                ##   in Loop: Header=BB2_1 Depth=1
	cmpl	$-1, -4(%rbp)
	setne	%al
	movb	%al, -17(%rbp)          ## 1-byte Spill
LBB2_3:                                 ##   in Loop: Header=BB2_1 Depth=1
	movb	-17(%rbp), %al          ## 1-byte Reload
	testb	$1, %al
	jne	LBB2_4
	jmp	LBB2_5
LBB2_4:                                 ##   in Loop: Header=BB2_1 Depth=1
	movq	-16(%rbp), %rdi
	movl	-4(%rbp), %esi
	callq	__Z11insert_headP5_nodei
	movq	%rax, -32(%rbp)         ## 8-byte Spill
	jmp	LBB2_1
LBB2_5:
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"%d"


.subsections_via_symbols
