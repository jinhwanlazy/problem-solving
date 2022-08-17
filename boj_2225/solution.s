	.arch armv8-a
	.text
	.const
__ZN6__pstl9execution2v1L3seqE:
	.space 1
__ZN6__pstl9execution2v1L3parE:
	.space 1
__ZN6__pstl9execution2v1L9par_unseqE:
	.space 1
__ZN6__pstl9execution2v1L5unseqE:
	.space 1
	.zerofill __DATA,__bss,__ZStL8__ioinit,1,0
	.const
	.align	2
__ZN9__gnu_cxxL21__default_lock_policyE:
	.word	2
	.align	3
__ZNSt8__detailL25__platform_wait_alignmentE:
	.xword	8
	.align	2
__ZNSt8__detailL21__atomic_spin_count_1E:
	.word	12
	.align	2
__ZNSt8__detailL21__atomic_spin_count_2E:
	.word	4
	.align	2
__ZNSt15regex_constantsL13error_collateE:
	.space 4
	.align	2
__ZNSt15regex_constantsL11error_ctypeE:
	.word	1
	.align	2
__ZNSt15regex_constantsL12error_escapeE:
	.word	2
	.align	2
__ZNSt15regex_constantsL13error_backrefE:
	.word	3
	.align	2
__ZNSt15regex_constantsL11error_brackE:
	.word	4
	.align	2
__ZNSt15regex_constantsL11error_parenE:
	.word	5
	.align	2
__ZNSt15regex_constantsL11error_braceE:
	.word	6
	.align	2
__ZNSt15regex_constantsL14error_badbraceE:
	.word	7
	.align	2
__ZNSt15regex_constantsL11error_rangeE:
	.word	8
	.align	2
__ZNSt15regex_constantsL11error_spaceE:
	.word	9
	.align	2
__ZNSt15regex_constantsL15error_badrepeatE:
	.word	10
	.align	2
__ZNSt15regex_constantsL16error_complexityE:
	.word	11
	.align	2
__ZNSt15regex_constantsL11error_stackE:
	.word	12
	.align	3
__ZNSt8__detailL19_S_invalid_state_idE:
	.xword	-1
	.align	3
__ZL3MOD:
	.xword	1000000000
	.cstring
	.align	3
lC0:
	.ascii "%lld \0"
	.align	3
lC1:
	.ascii "%d %d\0"
	.align	3
lC2:
	.ascii "%lld\12\0"
	.text
	.align	2
	.globl __Z5solvev
__Z5solvev:
LFB11494:
	sub	sp, sp, #3600
LCFI0:
	stp	x29, x30, [sp, 16]
LCFI1:
	add	x29, sp, 16
	str	x19, [sp, 32]
LCFI2:
	add	x0, sp, 56
	bl	__Z10init_tableILi21ELi21EEvRSt5arrayIS0_IxXT0_EEXT_EE
	str	wzr, [sp, 3596]
	b	L2
L5:
	str	wzr, [sp, 3592]
	b	L3
L4:
	ldrsw	x1, [sp, 3596]
	add	x0, sp, 56
	bl	__ZNSt5arrayIS_IxLm21EELm21EEixEm
	mov	x2, x0
	ldrsw	x0, [sp, 3592]
	mov	x1, x0
	mov	x0, x2
	bl	__ZNSt5arrayIxLm21EEixEm
	ldr	x0, [x0]
	str	x0, [sp]
	adrp	x0, lC0@PAGE
	add	x0, x0, lC0@PAGEOFF;momd
	bl	_printf
	ldr	w0, [sp, 3592]
	add	w0, w0, 1
	str	w0, [sp, 3592]
L3:
	ldrsw	x19, [sp, 3592]
	ldrsw	x1, [sp, 3596]
	add	x0, sp, 56
	bl	__ZNSt5arrayIS_IxLm21EELm21EEixEm
	bl	__ZNKSt5arrayIxLm21EE4sizeEv
	cmp	x19, x0
	cset	w0, cc
	and	w0, w0, 255
	cmp	w0, 0
	bne	L4
	mov	w0, 10
	bl	_putchar
	ldr	w0, [sp, 3596]
	add	w0, w0, 1
	str	w0, [sp, 3596]
L2:
	ldrsw	x19, [sp, 3596]
	add	x0, sp, 56
	bl	__ZNKSt5arrayIS_IxLm21EELm21EE4sizeEv
	cmp	x19, x0
	cset	w0, cc
	and	w0, w0, 255
	cmp	w0, 0
	bne	L5
	add	x0, sp, 48
	str	x0, [sp, 8]
	add	x0, sp, 52
	str	x0, [sp]
	adrp	x0, lC1@PAGE
	add	x0, x0, lC1@PAGEOFF;momd
	bl	_scanf
	ldr	w0, [sp, 48]
	sxtw	x1, w0
	add	x0, sp, 56
	bl	__ZNSt5arrayIS_IxLm21EELm21EEixEm
	mov	x2, x0
	ldr	w0, [sp, 52]
	sxtw	x0, w0
	mov	x1, x0
	mov	x0, x2
	bl	__ZNSt5arrayIxLm21EEixEm
	ldr	x0, [x0]
	str	x0, [sp, 3584]
	ldr	x0, [sp, 3584]
	str	x0, [sp]
	adrp	x0, lC2@PAGE
	add	x0, x0, lC2@PAGEOFF;momd
	bl	_printf
	nop
	ldr	x19, [sp, 32]
	ldp	x29, x30, [sp, 16]
	add	sp, sp, 3600
LCFI3:
	ret
LFE11494:
	.align	2
	.globl _main
_main:
LFB11495:
	stp	x29, x30, [sp, -32]!
LCFI4:
	mov	x29, sp
	mov	w0, 1
	str	w0, [sp, 28]
	b	L7
L8:
	bl	__Z5solvev
L7:
	ldr	w0, [sp, 28]
	sub	w1, w0, #1
	str	w1, [sp, 28]
	cmp	w0, 0
	cset	w0, ne
	and	w0, w0, 255
	cmp	w0, 0
	bne	L8
	mov	w0, 0
	ldp	x29, x30, [sp], 32
LCFI5:
	ret
LFE11495:
	.align	2
	.globl __ZNSt5arrayIxLm21EEixEm
	.weak_definition __ZNSt5arrayIxLm21EEixEm
__ZNSt5arrayIxLm21EEixEm:
LFB12356:
	stp	x29, x30, [sp, -32]!
LCFI6:
	mov	x29, sp
	str	x0, [sp, 24]
	str	x1, [sp, 16]
	ldr	x0, [sp, 24]
	ldr	x1, [sp, 16]
	bl	__ZNSt14__array_traitsIxLm21EE6_S_refERA21_Kxm
	ldp	x29, x30, [sp], 32
LCFI7:
	ret
LFE12356:
	.align	2
	.globl __ZNSt5arrayIS_IxLm21EELm21EEixEm
	.weak_definition __ZNSt5arrayIS_IxLm21EELm21EEixEm
__ZNSt5arrayIS_IxLm21EELm21EEixEm:
LFB12357:
	stp	x29, x30, [sp, -32]!
LCFI8:
	mov	x29, sp
	str	x0, [sp, 24]
	str	x1, [sp, 16]
	ldr	x0, [sp, 24]
	ldr	x1, [sp, 16]
	bl	__ZNSt14__array_traitsISt5arrayIxLm21EELm21EE6_S_refERA21_KS1_m
	ldp	x29, x30, [sp], 32
LCFI9:
	ret
LFE12357:
	.align	2
	.globl __Z10init_tableILi21ELi21EEvRSt5arrayIS0_IxXT0_EEXT_EE
	.weak_definition __Z10init_tableILi21ELi21EEvRSt5arrayIS0_IxXT0_EEXT_EE
__Z10init_tableILi21ELi21EEvRSt5arrayIS0_IxXT0_EEXT_EE:
LFB12355:
	stp	x29, x30, [sp, -80]!
LCFI10:
	mov	x29, sp
	str	x19, [sp, 16]
LCFI11:
	str	x0, [sp, 40]
	str	wzr, [sp, 76]
	b	L15
L16:
	ldrsw	x0, [sp, 76]
	mov	x1, x0
	ldr	x0, [sp, 40]
	bl	__ZNSt5arrayIS_IxLm21EELm21EEixEm
	mov	x1, 0
	bl	__ZNSt5arrayIxLm21EEixEm
	mov	x1, x0
	mov	x0, 1
	str	x0, [x1]
	ldr	w0, [sp, 76]
	add	w0, w0, 1
	str	w0, [sp, 76]
L15:
	ldr	w0, [sp, 76]
	cmp	w0, 21
	ble	L16
	mov	w0, 1
	str	w0, [sp, 72]
	b	L17
L18:
	mov	x1, 1
	ldr	x0, [sp, 40]
	bl	__ZNSt5arrayIS_IxLm21EELm21EEixEm
	mov	x2, x0
	ldrsw	x0, [sp, 72]
	mov	x1, x0
	mov	x0, x2
	bl	__ZNSt5arrayIxLm21EEixEm
	mov	x1, x0
	mov	x0, 1
	str	x0, [x1]
	ldr	w0, [sp, 72]
	add	w0, w0, 1
	str	w0, [sp, 72]
L17:
	ldr	w0, [sp, 72]
	cmp	w0, 21
	ble	L18
	mov	w0, 2
	str	w0, [sp, 68]
	b	L19
L24:
	mov	w0, 1
	str	w0, [sp, 64]
	b	L20
L23:
	str	wzr, [sp, 60]
	b	L21
L22:
	ldr	w0, [sp, 68]
	sub	w0, w0, #1
	sxtw	x0, w0
	mov	x1, x0
	ldr	x0, [sp, 40]
	bl	__ZNSt5arrayIS_IxLm21EELm21EEixEm
	mov	x2, x0
	ldr	w1, [sp, 64]
	ldr	w0, [sp, 60]
	sub	w0, w1, w0
	sxtw	x0, w0
	mov	x1, x0
	mov	x0, x2
	bl	__ZNSt5arrayIxLm21EEixEm
	ldr	x19, [x0]
	ldrsw	x0, [sp, 68]
	mov	x1, x0
	ldr	x0, [sp, 40]
	bl	__ZNSt5arrayIS_IxLm21EELm21EEixEm
	mov	x2, x0
	ldrsw	x0, [sp, 64]
	mov	x1, x0
	mov	x0, x2
	bl	__ZNSt5arrayIxLm21EEixEm
	ldr	x1, [x0]
	add	x1, x19, x1
	str	x1, [x0]
	ldrsw	x0, [sp, 68]
	mov	x1, x0
	ldr	x0, [sp, 40]
	bl	__ZNSt5arrayIS_IxLm21EELm21EEixEm
	mov	x2, x0
	ldrsw	x0, [sp, 64]
	mov	x1, x0
	mov	x0, x2
	bl	__ZNSt5arrayIxLm21EEixEm
	mov	x2, x0
	ldr	x1, [x2]
	mov	x0, 38067
	movk	x0, 0x26d6, lsl 16
	movk	x0, 0xbe8, lsl 32
	movk	x0, 0x112e, lsl 48
	smulh	x0, x1, x0
	asr	x3, x0, 26
	asr	x0, x1, 63
	sub	x0, x3, x0
	mov	x3, 51712
	movk	x3, 0x3b9a, lsl 16
	mul	x0, x0, x3
	sub	x0, x1, x0
	str	x0, [x2]
	ldr	w0, [sp, 60]
	add	w0, w0, 1
	str	w0, [sp, 60]
L21:
	ldr	w1, [sp, 60]
	ldr	w0, [sp, 64]
	cmp	w1, w0
	ble	L22
	ldr	w0, [sp, 64]
	add	w0, w0, 1
	str	w0, [sp, 64]
L20:
	ldr	w0, [sp, 64]
	cmp	w0, 21
	ble	L23
	ldr	w0, [sp, 68]
	add	w0, w0, 1
	str	w0, [sp, 68]
L19:
	ldr	w0, [sp, 68]
	cmp	w0, 21
	ble	L24
	nop
	nop
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 80
LCFI12:
	ret
LFE12355:
	.align	2
	.globl __ZNKSt5arrayIS_IxLm21EELm21EE4sizeEv
	.weak_definition __ZNKSt5arrayIS_IxLm21EELm21EE4sizeEv
__ZNKSt5arrayIS_IxLm21EELm21EE4sizeEv:
LFB12358:
	sub	sp, sp, #16
LCFI13:
	str	x0, [sp, 8]
	mov	x0, 21
	add	sp, sp, 16
LCFI14:
	ret
LFE12358:
	.align	2
	.globl __ZNKSt5arrayIxLm21EE4sizeEv
	.weak_definition __ZNKSt5arrayIxLm21EE4sizeEv
__ZNKSt5arrayIxLm21EE4sizeEv:
LFB12359:
	sub	sp, sp, #16
LCFI15:
	str	x0, [sp, 8]
	mov	x0, 21
	add	sp, sp, 16
LCFI16:
	ret
LFE12359:
	.align	2
	.globl __ZNSt14__array_traitsIxLm21EE6_S_refERA21_Kxm
	.weak_definition __ZNSt14__array_traitsIxLm21EE6_S_refERA21_Kxm
__ZNSt14__array_traitsIxLm21EE6_S_refERA21_Kxm:
LFB12810:
	sub	sp, sp, #16
LCFI17:
	str	x0, [sp, 8]
	str	x1, [sp]
	ldr	x0, [sp]
	lsl	x0, x0, 3
	ldr	x1, [sp, 8]
	add	x0, x1, x0
	add	sp, sp, 16
LCFI18:
	ret
LFE12810:
	.align	2
	.globl __ZNSt14__array_traitsISt5arrayIxLm21EELm21EE6_S_refERA21_KS1_m
	.weak_definition __ZNSt14__array_traitsISt5arrayIxLm21EELm21EE6_S_refERA21_KS1_m
__ZNSt14__array_traitsISt5arrayIxLm21EELm21EE6_S_refERA21_KS1_m:
LFB12811:
	sub	sp, sp, #16
LCFI19:
	str	x0, [sp, 8]
	str	x1, [sp]
	ldr	x1, [sp]
	mov	x0, x1
	lsl	x0, x0, 2
	add	x0, x0, x1
	lsl	x0, x0, 2
	add	x0, x0, x1
	lsl	x0, x0, 3
	ldr	x1, [sp, 8]
	add	x0, x1, x0
	add	sp, sp, 16
LCFI20:
	ret
LFE12811:
	.align	2
__Z41__static_initialization_and_destruction_0ii:
LFB13596:
	stp	x29, x30, [sp, -32]!
LCFI21:
	mov	x29, sp
	str	w0, [sp, 28]
	str	w1, [sp, 24]
	ldr	w0, [sp, 28]
	cmp	w0, 1
	bne	L35
	ldr	w1, [sp, 24]
	mov	w0, 65535
	cmp	w1, w0
	bne	L35
	adrp	x0, __ZStL8__ioinit@PAGE
	add	x0, x0, __ZStL8__ioinit@PAGEOFF;momd
	bl	__ZNSt8ios_base4InitC1Ev
	adrp	x0, ___dso_handle@PAGE
	add	x2, x0, ___dso_handle@PAGEOFF;momd
	adrp	x0, __ZStL8__ioinit@PAGE
	add	x1, x0, __ZStL8__ioinit@PAGEOFF;momd
	adrp	x0, __ZNSt8ios_base4InitD1Ev@GOTPAGE
	ldr	x0, [x0, __ZNSt8ios_base4InitD1Ev@GOTPAGEOFF];momd
	bl	___cxa_atexit
L35:
	nop
	ldp	x29, x30, [sp], 32
LCFI22:
	ret
LFE13596:
	.align	2
__GLOBAL__sub_I_solution.cpp:
LFB13619:
	stp	x29, x30, [sp, -16]!
LCFI23:
	mov	x29, sp
	mov	w1, 65535
	mov	w0, 1
	bl	__Z41__static_initialization_and_destruction_0ii
	ldp	x29, x30, [sp], 16
LCFI24:
	ret
LFE13619:
	.section __TEXT,__eh_frame,coalesced,no_toc+strip_static_syms+live_support
EH_frame1:
	.set L$set$0,LECIE1-LSCIE1
	.long L$set$0
LSCIE1:
	.long	0
	.byte	0x1
	.ascii "zR\0"
	.uleb128 0x1
	.sleb128 -8
	.byte	0x1e
	.uleb128 0x1
	.byte	0x10
	.byte	0xc
	.uleb128 0x1f
	.uleb128 0
	.align	3
LECIE1:
LSFDE1:
	.set L$set$1,LEFDE1-LASFDE1
	.long L$set$1
LASFDE1:
	.long	LASFDE1-EH_frame1
	.quad	LFB11494-.
	.set L$set$2,LFE11494-LFB11494
	.quad L$set$2
	.uleb128 0
	.byte	0x4
	.set L$set$3,LCFI0-LFB11494
	.long L$set$3
	.byte	0xe
	.uleb128 0xe10
	.byte	0x4
	.set L$set$4,LCFI1-LCFI0
	.long L$set$4
	.byte	0x9d
	.uleb128 0x1c0
	.byte	0x9e
	.uleb128 0x1bf
	.byte	0x4
	.set L$set$5,LCFI2-LCFI1
	.long L$set$5
	.byte	0x93
	.uleb128 0x1be
	.byte	0x4
	.set L$set$6,LCFI3-LCFI2
	.long L$set$6
	.byte	0xdd
	.byte	0xde
	.byte	0xd3
	.byte	0xe
	.uleb128 0
	.align	3
LEFDE1:
LSFDE3:
	.set L$set$7,LEFDE3-LASFDE3
	.long L$set$7
LASFDE3:
	.long	LASFDE3-EH_frame1
	.quad	LFB11495-.
	.set L$set$8,LFE11495-LFB11495
	.quad L$set$8
	.uleb128 0
	.byte	0x4
	.set L$set$9,LCFI4-LFB11495
	.long L$set$9
	.byte	0xe
	.uleb128 0x20
	.byte	0x9d
	.uleb128 0x4
	.byte	0x9e
	.uleb128 0x3
	.byte	0x4
	.set L$set$10,LCFI5-LCFI4
	.long L$set$10
	.byte	0xde
	.byte	0xdd
	.byte	0xe
	.uleb128 0
	.align	3
LEFDE3:
LSFDE5:
	.set L$set$11,LEFDE5-LASFDE5
	.long L$set$11
LASFDE5:
	.long	LASFDE5-EH_frame1
	.quad	LFB12356-.
	.set L$set$12,LFE12356-LFB12356
	.quad L$set$12
	.uleb128 0
	.byte	0x4
	.set L$set$13,LCFI6-LFB12356
	.long L$set$13
	.byte	0xe
	.uleb128 0x20
	.byte	0x9d
	.uleb128 0x4
	.byte	0x9e
	.uleb128 0x3
	.byte	0x4
	.set L$set$14,LCFI7-LCFI6
	.long L$set$14
	.byte	0xde
	.byte	0xdd
	.byte	0xe
	.uleb128 0
	.align	3
LEFDE5:
LSFDE7:
	.set L$set$15,LEFDE7-LASFDE7
	.long L$set$15
LASFDE7:
	.long	LASFDE7-EH_frame1
	.quad	LFB12357-.
	.set L$set$16,LFE12357-LFB12357
	.quad L$set$16
	.uleb128 0
	.byte	0x4
	.set L$set$17,LCFI8-LFB12357
	.long L$set$17
	.byte	0xe
	.uleb128 0x20
	.byte	0x9d
	.uleb128 0x4
	.byte	0x9e
	.uleb128 0x3
	.byte	0x4
	.set L$set$18,LCFI9-LCFI8
	.long L$set$18
	.byte	0xde
	.byte	0xdd
	.byte	0xe
	.uleb128 0
	.align	3
LEFDE7:
LSFDE9:
	.set L$set$19,LEFDE9-LASFDE9
	.long L$set$19
LASFDE9:
	.long	LASFDE9-EH_frame1
	.quad	LFB12355-.
	.set L$set$20,LFE12355-LFB12355
	.quad L$set$20
	.uleb128 0
	.byte	0x4
	.set L$set$21,LCFI10-LFB12355
	.long L$set$21
	.byte	0xe
	.uleb128 0x50
	.byte	0x9d
	.uleb128 0xa
	.byte	0x9e
	.uleb128 0x9
	.byte	0x4
	.set L$set$22,LCFI11-LCFI10
	.long L$set$22
	.byte	0x93
	.uleb128 0x8
	.byte	0x4
	.set L$set$23,LCFI12-LCFI11
	.long L$set$23
	.byte	0xde
	.byte	0xdd
	.byte	0xd3
	.byte	0xe
	.uleb128 0
	.align	3
LEFDE9:
LSFDE11:
	.set L$set$24,LEFDE11-LASFDE11
	.long L$set$24
LASFDE11:
	.long	LASFDE11-EH_frame1
	.quad	LFB12358-.
	.set L$set$25,LFE12358-LFB12358
	.quad L$set$25
	.uleb128 0
	.byte	0x4
	.set L$set$26,LCFI13-LFB12358
	.long L$set$26
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.set L$set$27,LCFI14-LCFI13
	.long L$set$27
	.byte	0xe
	.uleb128 0
	.align	3
LEFDE11:
LSFDE13:
	.set L$set$28,LEFDE13-LASFDE13
	.long L$set$28
LASFDE13:
	.long	LASFDE13-EH_frame1
	.quad	LFB12359-.
	.set L$set$29,LFE12359-LFB12359
	.quad L$set$29
	.uleb128 0
	.byte	0x4
	.set L$set$30,LCFI15-LFB12359
	.long L$set$30
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.set L$set$31,LCFI16-LCFI15
	.long L$set$31
	.byte	0xe
	.uleb128 0
	.align	3
LEFDE13:
LSFDE15:
	.set L$set$32,LEFDE15-LASFDE15
	.long L$set$32
LASFDE15:
	.long	LASFDE15-EH_frame1
	.quad	LFB12810-.
	.set L$set$33,LFE12810-LFB12810
	.quad L$set$33
	.uleb128 0
	.byte	0x4
	.set L$set$34,LCFI17-LFB12810
	.long L$set$34
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.set L$set$35,LCFI18-LCFI17
	.long L$set$35
	.byte	0xe
	.uleb128 0
	.align	3
LEFDE15:
LSFDE17:
	.set L$set$36,LEFDE17-LASFDE17
	.long L$set$36
LASFDE17:
	.long	LASFDE17-EH_frame1
	.quad	LFB12811-.
	.set L$set$37,LFE12811-LFB12811
	.quad L$set$37
	.uleb128 0
	.byte	0x4
	.set L$set$38,LCFI19-LFB12811
	.long L$set$38
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.set L$set$39,LCFI20-LCFI19
	.long L$set$39
	.byte	0xe
	.uleb128 0
	.align	3
LEFDE17:
LSFDE19:
	.set L$set$40,LEFDE19-LASFDE19
	.long L$set$40
LASFDE19:
	.long	LASFDE19-EH_frame1
	.quad	LFB13596-.
	.set L$set$41,LFE13596-LFB13596
	.quad L$set$41
	.uleb128 0
	.byte	0x4
	.set L$set$42,LCFI21-LFB13596
	.long L$set$42
	.byte	0xe
	.uleb128 0x20
	.byte	0x9d
	.uleb128 0x4
	.byte	0x9e
	.uleb128 0x3
	.byte	0x4
	.set L$set$43,LCFI22-LCFI21
	.long L$set$43
	.byte	0xde
	.byte	0xdd
	.byte	0xe
	.uleb128 0
	.align	3
LEFDE19:
LSFDE21:
	.set L$set$44,LEFDE21-LASFDE21
	.long L$set$44
LASFDE21:
	.long	LASFDE21-EH_frame1
	.quad	LFB13619-.
	.set L$set$45,LFE13619-LFB13619
	.quad L$set$45
	.uleb128 0
	.byte	0x4
	.set L$set$46,LCFI23-LFB13619
	.long L$set$46
	.byte	0xe
	.uleb128 0x10
	.byte	0x9d
	.uleb128 0x2
	.byte	0x9e
	.uleb128 0x1
	.byte	0x4
	.set L$set$47,LCFI24-LCFI23
	.long L$set$47
	.byte	0xde
	.byte	0xdd
	.byte	0xe
	.uleb128 0
	.align	3
LEFDE21:
	.private_extern ___dso_handle
	.ident	"GCC: (Homebrew GCC 11.3.0_2) 11.3.0"
	.mod_init_func
_Mod.init:
	.align	3
	.xword	__GLOBAL__sub_I_solution.cpp
	.subsections_via_symbols
