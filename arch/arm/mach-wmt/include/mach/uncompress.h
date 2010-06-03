/*
 * arch/arm/mach-wmt/include/mach/uncompress.h
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

#ifndef __ASM_ARCH_UNCOMPRESS_H
#define __ASM_ARCH_UNCOMPRESS_H

#include <linux/io.h>
#include <mach/hardware.h>

/*
 * The following code assumes the serial port has already been
 * initialized by the bootloader.  If you didn't setup a port in
 * your bootloader then nothing will appear (which might be desired).
 *
 * This does not append a newline
 */
static void putc(int c)
{
  void __iomem *sys = (void __iomem *) WM8505_UART0_BASE;	/* physical address */

	while (__raw_readl(sys + 0x1c) & 2)
	  barrier();
	__raw_writel(c, sys);
}

static inline void flush(void)
{
  void __iomem *sys = (void __iomem *) WM8505_UART0_BASE;	/* physical address */

	/* wait for transmission to complete */
  while (__raw_readl(sys + 0x1c) & 2)
    barrier();
}

#define arch_decomp_setup()

#define arch_decomp_wdog()

#endif
