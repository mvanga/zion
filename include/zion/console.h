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

#ifndef ZION_CONSOLE_H
#define ZION_CONSOLE_H

#include <zion/list.h>

struct console {
	int index;
	char name[16];
	void (*setup)(struct console *);
	void (*write)(struct console *, const char *, unsigned);
	int (*read)(struct console *, char *, unsigned);
	struct list_head list;
};

extern struct console *console_current;

int console_register(struct console *);
void console_unregister(struct console *);

void console_setup(struct console *);
void console_write(struct console *, const char *, unsigned);
int console_read(struct console *, char *, unsigned);

struct console *console_get(int);

#endif
