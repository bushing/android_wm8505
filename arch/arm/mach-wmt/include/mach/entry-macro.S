/*
 * arch/arm/mach-wmt/include/mach/entry-macro.S
 *
 * Low-level IRQ helper macros for WonderMedia platforms
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#include <mach/hardware.h>
#define CONFIG_ARCH_VT8610 1 // ?
	
        .macro  arch_ret_to_user, tmp1, tmp2
        .endm

	.macro  get_irqnr_preamble, base, tmp
	.endm

#ifdef IOC_BASE
	.macro  disable_fiq
	.endm
	
	.macro  get_irqnr_and_base, irqnr, irqstat, base, tmp
	ldr     \base, =IO_ADDRESS(VERSATILE_VIC_BASE)
	ldr     \irqstat, [\base, #VIC_IRQ_STATUS]      @ get masked status
	mov     \irqnr, #0
	teq     \irqstat, #0
	beq     1003f

1001:	tst     \irqstat, #15
	bne     1002f
	add     \irqnr, \irqnr, #4
	movs    \irqstat, \irqstat, lsr #4
	bne     1001b
1002:	tst     \irqstat, #1
	bne     1003f
	add     \irqnr, \irqnr, #1
	movs    \irqstat, \irqstat, lsr #1
	bne     1002b
1003:	/* EQ will be set if no irqs pending */

@               clz     \irqnr, \irqstat
@1003:          /* EQ will be set if we reach MAXIRQNUM */
        .endm

#elif defined(CONFIG_ARCH_VT8410)
        .macro  disable_fiq
	.endm

	.macro  get_irqnr_and_base, irqnr, irqstat, base, tmp
	mov     r4, #0xfa000000                 @ ICIP = 0xfa050000
	add     r4, r4, #0x00050000
	ldr     \irqstat, [r4]                  @ get irqs
	ldr     \irqnr, [r4, #4]                @ ICMR = 0xfa050004
	ands    \irqstat, \irqstat, \irqnr
	mov     \irqnr, #0
	beq     1001f
	tst     \irqstat, #0xff
	moveq   \irqstat, \irqstat, lsr #8      @ \irqstat >> 8
	addeq   \irqnr, \irqnr, #8
	tsteq   \irqstat, #0xff
	moveq   \irqstat, \irqstat, lsr #8
	addeq   \irqnr, \irqnr, #8
	tsteq   \irqstat, #0xff
	moveq   \irqstat, \irqstat, lsr #8
	addeq   \irqnr, \irqnr, #8
	tst     \irqstat, #0x0f
	moveq   \irqstat, \irqstat, lsr #4
	addeq   \irqnr, \irqnr, #4
	tst     \irqstat, #0x03
	moveq   \irqstat, \irqstat, lsr #2
	addeq   \irqnr, \irqnr, #2
	tst     \irqstat, #0x01
	addeqs  \irqnr, \irqnr, #1
1001:	
	.endm
	
	.macro  irq_prio_table
	.endm
#elif defined(CONFIG_ARCH_VT8420)
	.macro  disable_fiq
	@ TBD if need
	.endm
	
	.macro  get_irqnr_and_base, irqnr, irqstat, base, tmp
	mov     r4,     #0xf8000000
	add     r4, r4, #0x00420000             @ INTC_BASE
	ldr     \irqnr, [r4, #0x18]             @ get zac_irq, ICHS6 = 0xf8420018
	add     \irqstat, r4, #0xB0             @ save ICIS6A_ADDR to irqstat
	
	mov     \tmp, \irqnr                    @ tmp = logic shift index
	cmp     \tmp, #32                       @ (irqnr >= 32)?
	addhs   \irqstat, \irqstat, #4          @ (irqnr >= 32)? (irqstat+=4):
@                (irqstat=irqstat)
	subhs   \tmp, \tmp, #32
	ldr     \irqstat, [\irqstat]            @ get pending zac_irq bitmap
	mov     r4, #1
	mov     r4, r4, lsl \tmp                @ convert tmp to bitmap
	tst     r4, \irqstat                    @ Z set if not valid zac_irq
	.endm

	.macro  irq_prio_table
	@ TBD if need
	.endm

#elif defined(CONFIG_ARCH_VT8610)
	.macro  disable_fiq
	@ TBD if need
	.endm

	.macro  get_irqnr_and_base, irqnr, irqstat, base, tmp
	mov     r4,     #0xD8000000
	add     r4, r4, #0x00140000             @ INTC_BASE
	ldr     \irqnr, [r4, #0x00]             @ get zac_irq, ICHS6 = 0xD8140000
	
	cmp \irqnr, #0                      @ (tmp == 0 || tmp == 1)? //interrupt 1 irq or fiq
	cmpne   \irqnr, #1
	moveq   r4,     #0xD8000000
	addeq   r4, r4, #0x00150000             @ INTC1_BASE
	ldreq   \irqnr, [r4, #0x00]             @ get zac_irq, ICHS6 = 0xD8150000
	mov     \tmp, \irqnr                    @ tmp = logic shift index
	addeq   \irqnr, \irqnr,#64                      @ irq number + 64

	add     \irqstat, r4, #0x80             @ save ICIS6A_ADDR to irqstat
	cmp     \tmp, #32                       @ (irqnr >= 32)?
	addhs   \irqstat, \irqstat, #4          @ (irqnr >= 32)? (irqstat+=4):
@                (irqstat=irqstat)
	subhs   \tmp, \tmp, #32
	ldr     \irqstat, [\irqstat]            @ get pending zac_irq bitmap
	mov     r4, #1
	mov     r4, r4, lsl \tmp                @ convert tmp to bitmap
	tst     r4, \irqstat                    @ Z set if not valid zac_irq
	.endm

	.macro  irq_prio_table
	@ TBD if need
	.endm

#else
#error Unknown architecture
#endif
	