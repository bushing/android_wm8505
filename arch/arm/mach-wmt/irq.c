/*
 * linux/arch/arm/mach-wmt/irq.c
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/ioport.h>
#include <linux/sysdev.h>

#include <mach/hardware.h>
#include <asm/mach/irq.h>

#include "generic.h"

static void wmt_irq_ack(unsigned int irq)
{
}

static void wmt_irq_mask(unsigned int irq)
{
}

static void wmt_irq_unmask(unsigned int irq)
{
}

static int wmt_irq_set_type(unsigned int irq, unsigned int type)
{
  return 0;
}

static int wmt_irq_set_wake(unsigned int irq, unsigned int on)
{
  return 0;
}

static void wmt_irq_normal_ack(unsigned int irq)
{
}

static void wmt_irq_normal_unmask(unsigned int irq)
{
}

static int wmt_irq_alarm_set_wake(unsigned int irq, unsigned int on)
{
  return 0;
}

static int wmt_irq_suspend(struct sys_device *dev, pm_message_t state)
{
  return 0;
}

// fixme wrong prototype
static void wmt_irq_shutdown(unsigned int irq)
{
}

static struct irq_chip wmt_wake_chip = {
	.name		= "wake",
	.ack		= wmt_irq_ack,
	.mask		= wmt_irq_mask,
	.unmask		= wmt_irq_unmask,
	.set_type	= wmt_irq_set_type,
	.set_wake	= wmt_irq_set_wake,
};

static struct irq_chip wmt_gpio_chip = {
	.name		= "gpio",
	.ack		= wmt_irq_ack,
	.mask		= wmt_irq_mask,
	.unmask		= wmt_irq_unmask,
	.set_type	= wmt_irq_set_type,
};

static struct irq_chip wmt_normal_chip = {
	.name		= "normal",
	.ack		= wmt_irq_normal_ack,
	.mask		= wmt_irq_normal_ack,
	.unmask		= wmt_irq_normal_unmask,
};

static struct irq_chip wmt_alarm_chip = {
	.name		= "alarm",
	.ack		= wmt_irq_normal_ack,
	.mask		= wmt_irq_normal_ack,
	.unmask		= wmt_irq_normal_unmask,
	.set_wake	= wmt_irq_alarm_set_wake,
};

static struct resource irq_resource = {
	.name	= "irqs",
	.start	= 0xD8140000,
	.end	= 0xD815FFFF,
};

static struct sysdev_class wmt_irq_sysclass = {
	.name		= "rq",
	.shutdown	= wmt_irq_shutdown,
	.suspend	= wmt_irq_suspend,
};

static struct sys_device wmt_irq_device = {
	.id		= 0,
	.cls		= &wmt_irq_sysclass,
};

static int __init wmt_irq_device_init(void)
{
	sysdev_class_register(&wmt_irq_sysclass);
	return sysdev_register(&wmt_irq_device);
}

device_initcall(wmt_irq_device_init);

static unsigned short irq_table[] = {
  6, 7, 13, 14, 15, 52, 53, 54,
  0, 1, 2, 4, 5, 8, 9, 10,
  16, 17, 18, 19, 20, 21, 22, 23,
  24, 25, 26, 27, 28, 29, 30, 31,
  32, 33, 34, 35, 36, 37, 38, 39,
  40, 41, 42, 44, 45, 46, 47, 48,
  49, 50, 51, 55, 56, 57, 58, 59,
  60, 61, 62, 63, 65, 66, 79, 80,
  81, 82, 83, 84, 85, 86, 92, 93,
  94, 95, 96, 97, 98, 99, 111, 112,
  113, 114, 115, 0};

void __init wmt_init_irq(void)
{
	unsigned int irq;

	request_resource(&iomem_resource, &irq_resource);

	/* do stuff */
}
