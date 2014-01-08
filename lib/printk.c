/*
 * Zion: a capability-based microkernel for real-time systems
 * Copyright (C) 2013 Manohar vanga
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA  02110-1301, USA.
*/

#include <zion/console.h>
#include <zion/stdio.h>
#include <zion/stdarg.h>

#define PRINTK_BUFSIZE 128

static char printk_buf[PRINTK_BUFSIZE];

int getc(void)
{
	char c;

	return console_read(console_current, (char *)&c, 1);
}

char *gets(char *s, int size)
{
	int i = 0;
	while (i++ < size) {
		s[i-1] = getc();
		if (s[i-1] == '\n')
			break;
	}
	if (i > 0 && s[i-1] == '\n')
		s[i-1] = '\0';
	else
		s[i] = '\0';
	return s;
}

void putc(int c)
{
	console_write(console_current, (char *)&c, 1);
}

void puts(char *s)
{
	while (*s)
		putc(*s++);
}

int vprintk(const char *fmt, va_list args)
{
	int ret;

	ret = vsprintf(printk_buf, fmt, args);
	puts(printk_buf);
	return ret;
}

int printk(const char *fmt, ...)
{
	va_list args;
	int r;

	va_start(args, fmt);
	r = vprintk(fmt, args);
	va_end(args);

	return r;
}

int sprintf(char * buf, const char *fmt, ...)
{
	va_list args;
	int i;

	va_start(args, fmt);
	i=vsprintf(buf,fmt,args);
	va_end(args);
	return i;
}

