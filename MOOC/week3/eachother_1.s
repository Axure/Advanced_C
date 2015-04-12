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
	subq	$416, %rsp              ## imm = 0x1A0
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movl	$0, -340(%rbp)
	movl	%edi, -344(%rbp)
	movq	%rsi, -352(%rbp)
	movl	$0, -356(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$10, -356(%rbp)
	jge	LBB0_4
## BB#2:                                ##   in Loop: Header=BB0_1 Depth=1
	leaq	-336(%rbp), %rax
	movslq	-356(%rbp), %rcx
	shlq	$5, %rcx
	addq	%rcx, %rax
	movq	%rax, %rdi
	callq	__Z13student_inputP7Student
	movq	%rax, -368(%rbp)        ## 8-byte Spill
## BB#3:                                ##   in Loop: Header=BB0_1 Depth=1
	movl	-356(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -356(%rbp)
	jmp	LBB0_1
LBB0_4:
	leaq	L_.str(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	$0, -356(%rbp)
	movl	%eax, -372(%rbp)        ## 4-byte Spill
LBB0_5:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$10, -356(%rbp)
	jge	LBB0_8
## BB#6:                                ##   in Loop: Header=BB0_5 Depth=1
	leaq	L_.str1(%rip), %rdi
	movl	-356(%rbp), %eax
	addl	$1, %eax
	movl	%eax, %esi
	movb	$0, %al
	callq	_printf
	leaq	-336(%rbp), %rdi
	movslq	-356(%rbp), %rcx
	shlq	$5, %rcx
	addq	%rcx, %rdi
	movl	%eax, -376(%rbp)        ## 4-byte Spill
	callq	__Z13student_printPK7Student
## BB#7:                                ##   in Loop: Header=BB0_5 Depth=1
	movl	-356(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -356(%rbp)
	jmp	LBB0_5
LBB0_8:
	leaq	L_.str2(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	$0, -356(%rbp)
	movl	%eax, -380(%rbp)        ## 4-byte Spill
LBB0_9:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$3, -356(%rbp)
	jge	LBB0_12
## BB#10:                               ##   in Loop: Header=BB0_9 Depth=1
	leaq	-336(%rbp), %rdi
	movl	-356(%rbp), %esi
	callq	__Z13score_averagePK7Studenti
	leaq	L_.str3(%rip), %rdi
	movb	$1, %al
	callq	_printf
	movl	%eax, -384(%rbp)        ## 4-byte Spill
## BB#11:                               ##   in Loop: Header=BB0_9 Depth=1
	movl	-356(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -356(%rbp)
	jmp	LBB0_9
LBB0_12:
	leaq	L_.str4(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	$0, -356(%rbp)
	movl	%eax, -388(%rbp)        ## 4-byte Spill
LBB0_13:                                ## =>This Inner Loop Header: Depth=1
	cmpl	$3, -356(%rbp)
	jge	LBB0_16
## BB#14:                               ##   in Loop: Header=BB0_13 Depth=1
	leaq	-336(%rbp), %rdi
	movl	-356(%rbp), %esi
	callq	__Z13get_score_minPK7Studenti
	leaq	L_.str1(%rip), %rdi
	movl	%eax, %esi
	movb	$0, %al
	callq	_printf
	movl	%eax, -392(%rbp)        ## 4-byte Spill
## BB#15:                               ##   in Loop: Header=BB0_13 Depth=1
	movl	-356(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -356(%rbp)
	jmp	LBB0_13
LBB0_16:
	leaq	L_.str5(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	$0, -356(%rbp)
	movl	%eax, -396(%rbp)        ## 4-byte Spill
LBB0_17:                                ## =>This Inner Loop Header: Depth=1
	cmpl	$3, -356(%rbp)
	jge	LBB0_20
## BB#18:                               ##   in Loop: Header=BB0_17 Depth=1
	leaq	-336(%rbp), %rdi
	movl	-356(%rbp), %esi
	callq	__Z13get_score_maxPK7Studenti
	leaq	L_.str1(%rip), %rdi
	movl	%eax, %esi
	movb	$0, %al
	callq	_printf
	movl	%eax, -400(%rbp)        ## 4-byte Spill
## BB#19:                               ##   in Loop: Header=BB0_17 Depth=1
	movl	-356(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -356(%rbp)
	jmp	LBB0_17
LBB0_20:
	leaq	L_.str6(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	___stack_chk_guard@GOTPCREL(%rip), %rdi
	movq	(%rdi), %rdi
	cmpq	-8(%rbp), %rdi
	movl	%eax, -404(%rbp)        ## 4-byte Spill
	jne	LBB0_22
## BB#21:                               ## %SP_return
	movl	$0, %eax
	addq	$416, %rsp              ## imm = 0x1A0
	popq	%rbp
	retq
LBB0_22:                                ## %CallStackCheckFailBlk
	callq	___stack_chk_fail
	.cfi_endproc

	.globl	__Z13student_inputP7Student
	.align	4, 0x90
__Z13student_inputP7Student:            ## @_Z13student_inputP7Student
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
	subq	$32, %rsp
	leaq	L_.str7(%rip), %rax
	movq	%rdi, -8(%rbp)
	movq	%rax, %rdi
	movb	$0, %al
	callq	_printf
	leaq	L_.str8(%rip), %rdi
	movq	-8(%rbp), %rsi
	movq	-8(%rbp), %rcx
	addq	$20, %rcx
	movq	-8(%rbp), %rdx
	addq	$20, %rdx
	addq	$4, %rdx
	movq	-8(%rbp), %r8
	addq	$20, %r8
	addq	$8, %r8
	movq	%rdx, -16(%rbp)         ## 8-byte Spill
	movq	%rcx, %rdx
	movq	-16(%rbp), %rcx         ## 8-byte Reload
	movl	%eax, -20(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_scanf
	movq	-8(%rbp), %rcx
	movl	%eax, -24(%rbp)         ## 4-byte Spill
	movq	%rcx, %rax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.globl	__Z13student_printPK7Student
	.align	4, 0x90
__Z13student_printPK7Student:           ## @_Z13student_printPK7Student
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
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rsi
	movq	-8(%rbp), %rdi
	movl	20(%rdi), %edx
	movq	-8(%rbp), %rdi
	movl	24(%rdi), %ecx
	movq	-8(%rbp), %rdi
	movl	28(%rdi), %r8d
	movq	-8(%rbp), %rdi
	movq	%rsi, -16(%rbp)         ## 8-byte Spill
	movl	%edx, -20(%rbp)         ## 4-byte Spill
	movl	%ecx, -24(%rbp)         ## 4-byte Spill
	movl	%r8d, -28(%rbp)         ## 4-byte Spill
	callq	__Z15student_averagePK7Student
	leaq	L_.str9(%rip), %rdi
	movq	-16(%rbp), %rsi         ## 8-byte Reload
	movl	-20(%rbp), %edx         ## 4-byte Reload
	movl	-24(%rbp), %ecx         ## 4-byte Reload
	movl	-28(%rbp), %r8d         ## 4-byte Reload
	movb	$1, %al
	callq	_printf
	movl	%eax, -32(%rbp)         ## 4-byte Spill
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.globl	__Z13score_averagePK7Studenti
	.align	4, 0x90
__Z13score_averagePK7Studenti:          ## @_Z13score_averagePK7Studenti
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp17:
	.cfi_def_cfa_offset 16
Ltmp18:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp19:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	xorps	%xmm0, %xmm0
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movsd	%xmm0, -24(%rbp)
	movl	$0, -28(%rbp)
LBB3_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$10, -28(%rbp)
	jge	LBB3_4
## BB#2:                                ##   in Loop: Header=BB3_1 Depth=1
	movslq	-28(%rbp), %rax
	movq	-8(%rbp), %rcx
	shlq	$5, %rax
	addq	%rax, %rcx
	movl	-12(%rbp), %esi
	movq	%rcx, %rdi
	callq	__Z17student_get_scorePK7Studenti
	cvtsi2sdl	%eax, %xmm0
	movsd	-24(%rbp), %xmm1
	addsd	%xmm0, %xmm1
	movsd	%xmm1, -24(%rbp)
## BB#3:                                ##   in Loop: Header=BB3_1 Depth=1
	movl	-28(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -28(%rbp)
	jmp	LBB3_1
LBB3_4:
	movabsq	$10, %rax
	cvtsi2sdq	%rax, %xmm0
	movsd	-24(%rbp), %xmm1
	divsd	%xmm0, %xmm1
	movaps	%xmm1, %xmm0
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.globl	__Z13get_score_minPK7Studenti
	.align	4, 0x90
__Z13get_score_minPK7Studenti:          ## @_Z13get_score_minPK7Studenti
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp22:
	.cfi_def_cfa_offset 16
Ltmp23:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp24:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	$5, -16(%rbp)
	movl	$0, -20(%rbp)
LBB4_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$10, -20(%rbp)
	jge	LBB4_6
## BB#2:                                ##   in Loop: Header=BB4_1 Depth=1
	movslq	-20(%rbp), %rax
	movq	-8(%rbp), %rcx
	shlq	$5, %rax
	addq	%rax, %rcx
	movl	-12(%rbp), %esi
	movq	%rcx, %rdi
	callq	__Z17student_get_scorePK7Studenti
	movl	%eax, -24(%rbp)
	movl	-16(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jle	LBB4_4
## BB#3:                                ##   in Loop: Header=BB4_1 Depth=1
	movl	-24(%rbp), %eax
	movl	%eax, -16(%rbp)
LBB4_4:                                 ##   in Loop: Header=BB4_1 Depth=1
	jmp	LBB4_5
LBB4_5:                                 ##   in Loop: Header=BB4_1 Depth=1
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -20(%rbp)
	jmp	LBB4_1
LBB4_6:
	movl	-16(%rbp), %eax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.globl	__Z13get_score_maxPK7Studenti
	.align	4, 0x90
__Z13get_score_maxPK7Studenti:          ## @_Z13get_score_maxPK7Studenti
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp27:
	.cfi_def_cfa_offset 16
Ltmp28:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp29:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	$0, -16(%rbp)
	movl	$0, -20(%rbp)
LBB5_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$10, -20(%rbp)
	jge	LBB5_6
## BB#2:                                ##   in Loop: Header=BB5_1 Depth=1
	movslq	-20(%rbp), %rax
	movq	-8(%rbp), %rcx
	shlq	$5, %rax
	addq	%rax, %rcx
	movl	-12(%rbp), %esi
	movq	%rcx, %rdi
	callq	__Z17student_get_scorePK7Studenti
	movl	%eax, -24(%rbp)
	movl	-16(%rbp), %eax
	cmpl	-24(%rbp), %eax
	jge	LBB5_4
## BB#3:                                ##   in Loop: Header=BB5_1 Depth=1
	movl	-24(%rbp), %eax
	movl	%eax, -16(%rbp)
LBB5_4:                                 ##   in Loop: Header=BB5_1 Depth=1
	jmp	LBB5_5
LBB5_5:                                 ##   in Loop: Header=BB5_1 Depth=1
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -20(%rbp)
	jmp	LBB5_1
LBB5_6:
	movl	-16(%rbp), %eax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.globl	__Z15student_averagePK7Student
	.align	4, 0x90
__Z15student_averagePK7Student:         ## @_Z15student_averagePK7Student
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp32:
	.cfi_def_cfa_offset 16
Ltmp33:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp34:
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	xorps	%xmm0, %xmm0
	movq	%rdi, -8(%rbp)
	movsd	%xmm0, -16(%rbp)
	movl	$0, -20(%rbp)
LBB6_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$3, -20(%rbp)
	jge	LBB6_4
## BB#2:                                ##   in Loop: Header=BB6_1 Depth=1
	movq	-8(%rbp), %rdi
	movl	-20(%rbp), %esi
	callq	__Z17student_get_scorePK7Studenti
	cvtsi2sdl	%eax, %xmm0
	movsd	-16(%rbp), %xmm1
	addsd	%xmm0, %xmm1
	movsd	%xmm1, -16(%rbp)
## BB#3:                                ##   in Loop: Header=BB6_1 Depth=1
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -20(%rbp)
	jmp	LBB6_1
LBB6_4:
	movabsq	$3, %rax
	cvtsi2sdq	%rax, %xmm0
	movsd	-16(%rbp), %xmm1
	divsd	%xmm0, %xmm1
	movaps	%xmm1, %xmm0
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc

	.globl	__Z17student_get_scorePK7Studenti
	.align	4, 0x90
__Z17student_get_scorePK7Studenti:      ## @_Z17student_get_scorePK7Studenti
	.cfi_startproc
## BB#0:
	pushq	%rbp
Ltmp37:
	.cfi_def_cfa_offset 16
Ltmp38:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
Ltmp39:
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movslq	-12(%rbp), %rdi
	movq	-8(%rbp), %rax
	movl	20(%rax,%rdi,4), %eax
	popq	%rbp
	retq
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"\n\nno\tname\tscore1\tscore2\tscore3\taverage\n"

L_.str1:                                ## @.str1
	.asciz	"%d\t"

L_.str2:                                ## @.str2
	.asciz	"  \taverage\t"

L_.str3:                                ## @.str3
	.asciz	"%lf\t"

L_.str4:                                ## @.str4
	.asciz	"\n  \tmin\t"

L_.str5:                                ## @.str5
	.asciz	"\n  \tmax\t"

L_.str6:                                ## @.str6
	.asciz	"\n"

L_.str7:                                ## @.str7
	.asciz	" name    score1  score2  score3:\n"

L_.str8:                                ## @.str8
	.asciz	"%19s %1d %1d %1d"

L_.str9:                                ## @.str9
	.asciz	"%s\t%d\t%d\t%d\t%lf\n"


.subsections_via_symbols
