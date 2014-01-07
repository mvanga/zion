#include <zion/types.h>
#include <zion/jiffies.h>
#include <zion/stdio.h>

#include <arch/irq.h>
#include <arch/regs.h>
#include <arch/io.h>

static void timer_handler(struct regs *regs __attribute__((unused)))
{
	jiffies++;
}

int timer_init(void)
{
	uint32_t divisor;

	request_irq(0, &timer_handler);

	divisor = 1193180 / HZ;
	outb(0x36, 0x43);
	outb(divisor & 0xff, 0x40);
	outb((divisor >> 8) & 0xff, 0x40);

	return 0;
}
