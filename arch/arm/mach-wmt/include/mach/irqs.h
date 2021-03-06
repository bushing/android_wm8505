/*
 * arch/arm/mach-wmt/include/mach/irqs.h
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __ASM_ARCH_IRQS_H
#define __ASM_ARCH_IRQS_H

#include <linux/io.h>

/*
 * Acknowledge interrupt with AIC after interrupt has been handled.
 *   (by kernel/irq.c)
 */
#define irq_finish(irq) do { } while (0)

#define	NR_IRQS		64 // ?

/* FIQ is AIC source 0. */
//#define FIQ_START AT91_ID_FIQ

#endif
