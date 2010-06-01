/*
 * arch/arm/mach-wmt/include/mach/debug-macro.S
 *
 * Debugging macro include header
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
*/

#include <mach/hardware.h>
	
	.macro	addruart,rx
	ldr \rx, =(WM8505_UART0_BASE)
	.endm

	
	.macro	senduart,rd,rx
	strb	\rd, [\rx]	@ Write to Transmitter Holding Register
	.endm

	.macro	waituart,rd,rx
1001:	ldr	\rd, [\rx, #0x1C]		@ Read Status Register
	tst	\rd, #2				                @ URUSR & 2 = 0 when ready to transmit
	bne	1001b
	.endm

	.macro busyuart,rd,rx
	.endm
	