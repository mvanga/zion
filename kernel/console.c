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
#include <zion/list.h>
#include <zion/stdio.h>

static LIST_HEAD(consoles);

struct console *console_current;

int console_register(struct console *c)
{
	if (!c)
		return -1;
	if (c->index == 0)
		console_current = c;
	list_add(&c->list, &consoles);
	if (c->setup)
		c->setup(c);
	return 0;
}

void console_unregister(struct console *c)
{
	if (!c)
		return;
	list_del(&c->list);
}

void console_setup(struct console *c)
{
	if (!c || !c->setup)
		return;
	c->setup(c);
}

void console_write(struct console *c, const char *buf, unsigned len)
{
	if (!c || !c->write)
		return;
	c->write(c, buf, len);
}

int console_read(struct console *c, char *buf, unsigned len)
{
	if (!c || !c->read)
		return -1;
	return c->read(c, buf, len);
}

struct console *console_get(int idx)
{
	struct console *c;

	list_for_each_entry(c, &consoles, list) {
		if (c->index == idx)
			return c;
	}
	return NULL;
}
