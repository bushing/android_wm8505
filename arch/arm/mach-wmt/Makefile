#
# Makefile for the linux kernel.
#

obj-y		:= generic.o irq.o
obj-m		:=
obj-n		:=
obj-		:=

#obj-$(CONFIG_AT91_PMC_UNIT)	+= clock.o

# CPU-specific support
#obj-$(CONFIG_ARCH_WMT)	+= at91rm9200.o at91rm9200_time.o at91rm9200_devices.o

# Drivers
#obj-y				+= leds.o

# Power Management
#obj-$(CONFIG_PM)		+= pm.o
#obj-$(CONFIG_AT91_SLOW_CLOCK)	+= pm_slowclock.o

ifeq ($(CONFIG_PM_DEBUG),y)
#CFLAGS_pm.o += -DDEBUG
endif
