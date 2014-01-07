#include <zion/stdio.h>
#include <zion/console.h>
#include <zion/types.h>
#include <zion/jiffies.h>

int main(void)
{
	while (1) {
		printk(".");
		delay(1000);
	}
	return 0;
}
