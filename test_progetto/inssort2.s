	.text
	.file	"inssort2.ll"
	.section	.rodata.cst8,"aM",@progbits,8
	.p2align	3, 0x0                          # -- Begin function inssort
.LCPI0_0:
	.quad	0x4024000000000000              # double 10
.LCPI0_1:
	.quad	0xbff0000000000000              # double -1
.LCPI0_2:
	.quad	0x3ff0000000000000              # double 1
	.text
	.globl	inssort
	.p2align	4, 0x90
	.type	inssort,@function
inssort:                                # @inssort
	.cfi_startproc
# %bb.0:                                # %entry
	movabsq	$4607182418800017408, %rax      # imm = 0x3FF0000000000000
	movq	%rax, -16(%rsp)
	movsd	.LCPI0_0(%rip), %xmm0           # xmm0 = mem[0],zero
	movq	A@GOTPCREL(%rip), %rax
	movsd	.LCPI0_1(%rip), %xmm1           # xmm1 = mem[0],zero
	movsd	.LCPI0_2(%rip), %xmm2           # xmm2 = mem[0],zero
	jmp	.LBB0_1
	.p2align	4, 0x90
.LBB0_6:                                # %afterLoop6
                                        #   in Loop: Header=BB0_1 Depth=1
	movsd	-8(%rsp), %xmm3                 # xmm3 = mem[0],zero
	movsd	-24(%rsp), %xmm4                # xmm4 = mem[0],zero
	addsd	%xmm2, %xmm4
	cvtsd2ss	%xmm4, %xmm4
	cvttss2si	%xmm4, %ecx
	movslq	%ecx, %rcx
	leaq	(%rcx,%rcx,4), %rcx
	shlq	$4, %rcx
	movsd	%xmm3, (%rax,%rcx)
	movsd	-16(%rsp), %xmm3                # xmm3 = mem[0],zero
	addsd	%xmm2, %xmm3
	movsd	%xmm3, -16(%rsp)
.LBB0_1:                                # %cond
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_3 Depth 2
	movsd	-16(%rsp), %xmm3                # xmm3 = mem[0],zero
	ucomisd	%xmm0, %xmm3
	jae	.LBB0_7
# %bb.2:                                # %loop
                                        #   in Loop: Header=BB0_1 Depth=1
	movsd	-16(%rsp), %xmm3                # xmm3 = mem[0],zero
	xorps	%xmm4, %xmm4
	cvtsd2ss	%xmm3, %xmm4
	cvttss2si	%xmm4, %ecx
	movslq	%ecx, %rcx
	leaq	(%rcx,%rcx,4), %rcx
	shlq	$4, %rcx
	movsd	(%rax,%rcx), %xmm4              # xmm4 = mem[0],zero
	movsd	%xmm4, -8(%rsp)
	addsd	%xmm1, %xmm3
	.p2align	4, 0x90
.LBB0_3:                                # %cond4
                                        #   Parent Loop BB0_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movsd	%xmm3, -24(%rsp)
	movsd	-24(%rsp), %xmm3                # xmm3 = mem[0],zero
	ucomisd	%xmm3, %xmm1
	jae	.LBB0_6
# %bb.4:                                # %cond4
                                        #   in Loop: Header=BB0_3 Depth=2
	cvtsd2ss	%xmm3, %xmm3
	cvttss2si	%xmm3, %ecx
	movslq	%ecx, %rcx
	leaq	(%rcx,%rcx,4), %rcx
	shlq	$4, %rcx
	movsd	-8(%rsp), %xmm3                 # xmm3 = mem[0],zero
	ucomisd	(%rax,%rcx), %xmm3
	jae	.LBB0_6
# %bb.5:                                # %loop5
                                        #   in Loop: Header=BB0_3 Depth=2
	movsd	-24(%rsp), %xmm3                # xmm3 = mem[0],zero
	xorps	%xmm4, %xmm4
	cvtsd2ss	%xmm3, %xmm4
	cvttss2si	%xmm4, %ecx
	movslq	%ecx, %rcx
	leaq	(%rcx,%rcx,4), %rcx
	shlq	$4, %rcx
	movsd	(%rax,%rcx), %xmm4              # xmm4 = mem[0],zero
	addsd	%xmm2, %xmm3
	cvtsd2ss	%xmm3, %xmm3
	cvttss2si	%xmm3, %ecx
	movslq	%ecx, %rcx
	leaq	(%rcx,%rcx,4), %rcx
	shlq	$4, %rcx
	movsd	%xmm4, (%rax,%rcx)
	movsd	-24(%rsp), %xmm3                # xmm3 = mem[0],zero
	subsd	%xmm2, %xmm3
	jmp	.LBB0_3
.LBB0_7:                                # %afterLoop
	xorpd	%xmm0, %xmm0
	retq
.Lfunc_end0:
	.size	inssort, .Lfunc_end0-inssort
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst8,"aM",@progbits,8
	.p2align	3, 0x0                          # -- Begin function main
.LCPI1_0:
	.quad	0x4024000000000000              # double 10
.LCPI1_1:
	.quad	0x3ff0000000000000              # double 1
	.text
	.globl	main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbx
	.cfi_def_cfa_offset 16
	subq	$32, %rsp
	.cfi_def_cfa_offset 48
	.cfi_offset %rbx, -16
	callq	timek@PLT
	movsd	%xmm0, 24(%rsp)
	callq	randinit@PLT
	movq	$0, 8(%rsp)
	movq	A@GOTPCREL(%rip), %rbx
	.p2align	4, 0x90
.LBB1_1:                                # %cond
                                        # =>This Inner Loop Header: Depth=1
	movsd	8(%rsp), %xmm0                  # xmm0 = mem[0],zero
	ucomisd	.LCPI1_0(%rip), %xmm0
	jae	.LBB1_3
# %bb.2:                                # %loop
                                        #   in Loop: Header=BB1_1 Depth=1
	callq	randk@PLT
	movsd	8(%rsp), %xmm1                  # xmm1 = mem[0],zero
	cvtsd2ss	%xmm1, %xmm1
	cvttss2si	%xmm1, %eax
	cltq
	leaq	(%rax,%rax,4), %rax
	shlq	$4, %rax
	movsd	%xmm0, (%rbx,%rax)
	movsd	8(%rsp), %xmm0                  # xmm0 = mem[0],zero
	cvtsd2ss	%xmm0, %xmm0
	cvttss2si	%xmm0, %eax
	cltq
	leaq	(%rax,%rax,4), %rax
	shlq	$4, %rax
	movsd	(%rbx,%rax), %xmm0              # xmm0 = mem[0],zero
	xorps	%xmm1, %xmm1
	callq	printval@PLT
	movsd	8(%rsp), %xmm0                  # xmm0 = mem[0],zero
	addsd	.LCPI1_1(%rip), %xmm0
	movsd	%xmm0, 8(%rsp)
	jmp	.LBB1_1
.LBB1_3:                                # %afterLoop
	xorpd	%xmm0, %xmm0
	movsd	.LCPI1_1(%rip), %xmm1           # xmm1 = mem[0],zero
	callq	printval@PLT
	callq	inssort@PLT
	movq	$0, 16(%rsp)
	.p2align	4, 0x90
.LBB1_4:                                # %cond12
                                        # =>This Inner Loop Header: Depth=1
	movsd	16(%rsp), %xmm0                 # xmm0 = mem[0],zero
	ucomisd	.LCPI1_0(%rip), %xmm0
	jae	.LBB1_6
# %bb.5:                                # %loop13
                                        #   in Loop: Header=BB1_4 Depth=1
	movsd	16(%rsp), %xmm0                 # xmm0 = mem[0],zero
	cvtsd2ss	%xmm0, %xmm0
	cvttss2si	%xmm0, %eax
	cltq
	leaq	(%rax,%rax,4), %rax
	shlq	$4, %rax
	movsd	(%rbx,%rax), %xmm0              # xmm0 = mem[0],zero
	xorps	%xmm1, %xmm1
	callq	printval@PLT
	movsd	16(%rsp), %xmm0                 # xmm0 = mem[0],zero
	addsd	.LCPI1_1(%rip), %xmm0
	movsd	%xmm0, 16(%rsp)
	jmp	.LBB1_4
.LBB1_6:                                # %afterLoop14
	xorpd	%xmm0, %xmm0
	addq	$32, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc
                                        # -- End function
	.type	A,@object                       # @A
	.bss
	.globl	A
	.p2align	4, 0x0
A:
	.zero	80
	.size	A, 80

	.section	".note.GNU-stack","",@progbits
