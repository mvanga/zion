include .config

NAME=zion
ARCH=x86

obj-$(CONFIG_ARCH_X86) += arch/x86/boot.o \
	arch/x86/init.o \
	arch/x86/early_printk.o \
	arch/x86/gdt.o \
	arch/x86/idt.o \
	arch/x86/irq.o \
	arch/x86/segment.o \
	arch/x86/timer.o \
	arch/x86/kmalloc.o

obj-y += kernel/console.o \
	kernel/timer.o \
	kernel/main.o

obj-y += lib/atoi.o \
	lib/string.o \
	lib/strtol.o \
	lib/vsprintf.o \
	lib/printk.o \
	lib/ctype.o \
	lib/rand.o

CC	?= $(CROSS_COMPILE)gcc
AS	?= $(CROSS_COMPILE)as
LD	?= $(CROSS_COMPILE)ld

CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector \
	-I./arch/$(ARCH)/include -I./include \
	-Wall -Wextra -ggdb
LDFLAGS=-Tarch/$(ARCH)/link.ld

all: $(obj-y) link bin

clean:
	rm -rf $(obj-y) $(NAME) $(NAME).bin

link:
	ld $(LDFLAGS) -o $(NAME) $(obj-y)

bin:
	objcopy -Obinary $(NAME) $(NAME).bin

run: clean all
	qemu-system-i386 -kernel $(NAME)
