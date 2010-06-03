/*
 *  drivers/serial/serial_wmt.c
 *
 * Copyright (c) 2006  VIA Technologies, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 */
#include <linux/module.h>
#include <linux/tty.h>
#include <linux/ioport.h>
#include <linux/init.h>
#include <linux/serial.h>
#include <linux/console.h>
#include <linux/sysrq.h>
#include <linux/device.h>

#include <asm/io.h>
#include <asm/irq.h>
#include <asm/mach/irq.h>

#include <mach/regs-uart.h>
#include <mach/regs-irq.h>

#include <linux/serial_core.h>

PUART_REG       pUart_Reg = (PUART_REG)BA_UART0;
PGPIO_REG       pGpioReg = (PGPIO_REG)BA_GPIO;

#define SERIAL_WMT_MAJOR	4
#define SERIAL_WMT_MINOR	64
#define SERIAL_WMT_DEVNAME	"ttyS"

#define SERIAL_WMT_NR	6

#ifdef CONFIG_SERIAL_WMT_CONSOLE
static void wmt_console_putchar(struct uart_port *port, int ch)
{
  while (pUart_Reg->URUSR & URUSR_TXDBSY)
    barrier();

  pUart_Reg->URTDR = ch;
}

static void wmt_console_write(struct console *co, const char *s, u_int count)
{
	struct uart_port *port = wmt_ports + co->index;

	uart_console_write(port, s, count, wmt_console_putchar);
}

static void __init wmt_console_get_options(struct uart_port *port, int *baud, int *parity, int *bits)
{
	unsigned int lcr;
#if 0
	lcr = UART_GET_LCR(port);

	switch (lcr & URLC_PARITY) {
		case URPE_ODD:
			*parity = 'o';
			break;
		case URPE_EVEN:
			*parity = 'e';
			break;
		default:
			*parity = 'n';
	}

	switch (lcr & URLC_URCL) {
		case URCL_5:
			*bits = 5;
			break;
		case URCL_6:
			*bits = 6;
			break;
		case URCL_7:
			*bits = 7;
			break;
		default:
			*bits = 8;
	}

	*baud = port->uartclk / (UART_GET_BRDR(port) & 0x0FFF);
	*baud /= 16;
	*baud &= 0xFFFFFFF0;
#endif
}

static int __init wmt_console_setup(struct console *co, char *options)
{
	struct uart_port *port;
	int baud = 115200;
	int bits = 8;
	int parity = 'n';
	int flow = 'n';

	/*
	 * Check whether an invalid uart number has been specified, and
	 * if so, search for the first available port that does have
	 * console support.
	 */
	port = uart_get_console(wmt_uart_ports, SERIAL_WMT_NR, co);

	if (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);
	else
		wmt_console_get_options(port, &baud, &parity, &bits);

	return uart_set_options(port, co, baud, parity, bits, flow);
}

static struct uart_driver wmt_reg;

static struct console wmt_console = {
	.name		= SERIAL_WMT_DEVNAME,
	.write		= wmt_console_write,
	.device		= uart_console_device,
	.setup		= wmt_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &wmt_reg,
};

static int __init wmt_console_init(void)
{
	register_console(&wmt_console);
	return 0;
}

console_initcall(wmt_console_init);

#define WMT_CONSOLE	&wmt_console
#else
#define WMT_CONSOLE	NULL
#endif

static struct uart_driver wmt_uart_reg = {
	.owner			= THIS_MODULE,
	.driver_name		= "ttyS",
	.dev_name		= SERIAL_WMT_DEVNAME,
	.major			= SERIAL_WMT_MAJOR,
	.minor			= SERIAL_WMT_MINOR,
	.nr			= SERIAL_WMT_NR,
	.cons			= KS8695_CONSOLE,
};

static struct platform_driver wmt_serial_driver = {
  .probe          = wmt_serial_probe,
  .remove         = wmt_serial_remove,
  .suspend        = wmt_serial_suspend,
  .resume         = wmt_serial_resume,
  .driver         = {
    .name   = "uart",
    .owner  = THIS_MODULE,
  },
};

static void wmt_init_ports(void) {
  // sub_C01D4E68
}

static int __init wmt_uart_init(void)
{
  int ret;

  printk(KERN_INFO "starting wmt serial driver\n");

  wmt_init_ports();

  ret = uart_register_driver(&wmt_uart_reg);
  if (ret == 0) {
    ret = platform_driver_register(&wmt_serial_driver);
    if (ret)
      uart_unregister_driver(&wmt_uart_reg);
  }

  printk(KERN_INFO "WMT Serial driver initialized: %s\n", ret?"ok":"failed");
  return ret;
}
