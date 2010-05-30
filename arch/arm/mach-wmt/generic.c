/*
 *  arch/arm/mach-wmt/generic.c
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
 *
 */
#include <linux/platform_device.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>

#include <asm/errno.h>
#include <asm/delay.h>
#include <mach/hardware.h>

#include <asm/mach/map.h>
#include <mach/gpio.h>

#define write16(a,v)        (*(volatile unsigned short *)(a) = (v))
#define write32(a,v)        (*(volatile unsigned int   *)(a) = (v))
#define read32(a)        (*(volatile unsigned int   *)(a))

static struct resource uart0_resources[] = {
  [0] = {
    .start = 0xD8200000,
    .end = 0xD820FFFF,
    .flags = IORESOURCE_MEM,
  },
};

static struct resource uart1_resources[] = {
  [0] = {
    .start = 0xD82B0000,
    .end = 0xD82BFFFF,
    .flags = IORESOURCE_MEM,
  },
};

static struct resource uart2_resources[] = {
  [0] = {
    .start = 0xD8210000,
    .end = 0xD821FFFF,
    .flags = IORESOURCE_MEM,
  },
};

static struct resource uart3_resources[] = {
  [0] = {
    .start = 0xD82C0000,
    .end = 0xD82CFFFF,
    .flags = IORESOURCE_MEM,
  },
};

static struct resource uart4_resources[] = {
  [0] = {
    .start = 0xD8370000,
    .end = 0xD837FFFF,
    .flags = IORESOURCE_MEM,
  },
};

static struct resource uart5_resources[] = {
  [0] = {
    .start = 0xD8380000,
    .end = 0xD838FFFF,
    .flags = IORESOURCE_MEM,
  },
};

static u64 sdmmc_dmamask = 0xffffffffUL;
static struct resource sdmmc_resources[] = {
	[0] = {
	  .start = 0xD800A000,
	  .end = 0xD800A3FF,
	  .flags = IORESOURCE_MEM,
	},
	[1] = {
	  .start = 0x14,
	  .end = 0x14,
	  .flags = IORESOURCE_IRQ,
	},
	[2] = {
	  .start = 0x15,
	  .end = 0x15,
	  .flags = IORESOURCE_IRQ,
	},
	[3] = {
	  .start = 0x16,
	  .end = 0x16,
	  .flags = IORESOURCE_IRQ,
	},
};


static struct resource sf_resources[] = {
  [0] = {
    .start = 0xD8002000,
    .end = 0xD80023FF,
    .flags = IORESOURCE_MEM,
  },
};

static struct resource nor_resources[] = {
  [0] = {
    .start = 0xD8009400,
    .end = 0xD8009F00,
    .flags = IORESOURCE_MEM,
  },
};

static u64 nand_dmamask = 0xffffffffUL;
static struct resource nand_resources[] = {
  [0] = {
    .start = 0xD8009000,
    .end = 0xD80093FF,
    .flags = IORESOURCE_MEM,
  },
};

static u64 i2s_dmamask = 0xffffffffUL;
static struct resource i2s_resources[] = {
  [0] = {
    .start = 0xD8330000,
    .end = 0xD833FFFF,
    .flags = IORESOURCE_MEM,
  },
};

static u64 pcm_dmamask = 0xffffffffUL;
static struct resource pcm_resources[] = {
  [0] = {
    .start = 0xD82D0000,
    .end = 0xD82DFFFF,
    .flags = IORESOURCE_MEM,
  },
};

static struct resource kpad_resources[] = {
  [0] = {
    .start = 0xD8002000,
    .end = 0xD80023FF,
    .flags = IORESOURCE_MEM,
  },
  [1] = {
    .start = 0x8,
    .end = 0x8,
    .flags = IORESOURCE_IRQ,
  },
};

static u64 wmt_battery_dmamask = 0UL; // ??

static struct platform_device device_uart0 = {
  .name = "uart",
  .id = 0,
  .num_resources = ARRAY_SIZE(uart0_resources),
  .resource = uart0_resources,
};

static struct platform_device device_uart1 = {
  .name = "uart",
  .id = 1,
  .num_resources = ARRAY_SIZE(uart1_resources),
  .resource = uart1_resources,
};

static struct platform_device device_uart2 = {
  .name = "uart",
  .id = 2,
  .num_resources = ARRAY_SIZE(uart2_resources),
  .resource = uart2_resources,
};

static struct platform_device device_uart3 = {
  .name = "uart",
  .id = 3,
  .num_resources = ARRAY_SIZE(uart3_resources),
  .resource = uart3_resources,
};

static struct platform_device device_uart4 = {
  .name = "uart",
  .id = 4,
  .num_resources = ARRAY_SIZE(uart4_resources),
  .resource = uart4_resources,
};

static struct platform_device device_uart5 = {
  .name = "uart",
  .id = 5,
  .num_resources = ARRAY_SIZE(uart5_resources),
  .resource = uart5_resources,
};

static struct platform_device device_sdmmc = {
  .name = "sdmmc",
  .id = 0,
  .dev = {
    .dma_mask = &sdmmc_dmamask,
    .coherent_dma_mask = 0xffffffff,
  },
  .num_resources = ARRAY_SIZE(sdmmc_resources),
  .resource = sdmmc_resources,
};

static struct platform_device device_sf = {
  .name = "sf",
  .id = 0,
  .num_resources = ARRAY_SIZE(sf_resources),
  .resource = sf_resources,
};

static struct platform_device device_nor = {
  .name = "nor",
  .id = 0,
  .num_resources = ARRAY_SIZE(nor_resources),
  .resource = nor_resources,
};

static struct platform_device device_nand = {
  .name = "nand",
  .id = 0,
  .dev = {
    .dma_mask = &nand_dmamask,
    .coherent_dma_mask = 0xffffffff,
  },
  .num_resources = ARRAY_SIZE(nand_resources),
  .resource = nand_resources,
};

static struct platform_device device_i2s = {
  .name = "i2s",
  .id = 0,
  .dev = {
    .dma_mask = &i2s_dmamask,
    .coherent_dma_mask = 0xffffffff,
  },
  .num_resources = ARRAY_SIZE(i2s_resources),
  .resource = i2s_resources,
};

static struct platform_device device_pcm = {
  .name = "pcm",
  .id = 0,
  .dev = {
    .dma_mask = &pcm_dmamask,
    .coherent_dma_mask = 0xffffffff,
  },
  .num_resources = ARRAY_SIZE(pcm_resources),
  .resource = pcm_resources,
};

static struct platform_device device_kpad = {
  .name = "kpad",
  .id = 0,
  .num_resources = ARRAY_SIZE(kpad_resources),
  .resource = kpad_resources,
};

static struct platform_device device_wmt_battery = {
  .name = "wmt_battery",
  .id = -1,
  .dev = {
    .dma_mask = &wmt_battery_dmamask,
    .coherent_dma_mask = 0, // ??
  },
  .num_resources = 0,
};

static struct platform_device *devices[] __initdata = {
  &device_uart0,
  &device_uart1,
  &device_uart2,
  &device_uart3,
  &device_uart4,
  &device_uart5,
  &device_sdmmc,
  &device_sf,
  &device_nor,
  &device_nand,
  &device_i2s,
  &device_pcm,
  &device_kpad,
  &device_wmt_battery,
};

static void wmt_power_off(void)
{
  int i;
  printk(KERN_ERR "wmt_power_off()\n");
  for (i=0; i < 100; i++) __const_udelay(0x66665B0);
  __asm__ ("mrs r0, CPSR\n\t"
	   "orr r0, r0, #0x80\n\t"
	   "msr CPSR, r0");

  write32(0xD8130030, 0);
  write32(0xD8130118, read32(0xD8130118) & 0xFFFFFFFE);
  write16(0xD8130012, 5);
  __asm__ ("mcr p15, 0, r0, c7, c0, 4");

}

static int __init wmt_init(void)
{
  unsigned short *ptr;
  printk(KERN_ERR "wmt_init()\n");
  ptr = __arm_ioremap(0xFFFF0000, 0x10000, 0);
  if (ptr[0xFFF4]) {
    // BUG()?
    printk(KERN_ERR "bug? ptr[0xFFF4] = %04hx\n", ptr[0xFFF4]);
  }

  pm_power_off = wmt_power_off;
  
  return platform_add_devices(devices, ARRAY_SIZE(devices));
}

subsys_initcall(wmt_init);
