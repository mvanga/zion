NAME=zion
ARCH=x86

obj-y += kernel/console.o

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
