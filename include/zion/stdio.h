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

#ifndef ZION_STDIO_H
#define ZION_STDIO_H

#include <zion/stdarg.h>

int getc(void);
char *gets(char *s, int size);
void putc(int c);
void puts(char *s);
int vprintk(const char *fmt, va_list args);
int printk(const char *fmt, ...);
int sprintf(char * buf, const char *fmt, ...);
int vsprintf(char *buf, const char *fmt, va_list args);

#endif
