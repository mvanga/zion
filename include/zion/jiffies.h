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

#ifndef ZION_JIFFIES_H
#define ZION_JIFFIES_H

#include <zion/types.h>

#define HZ	1000

extern volatile uint32_t jiffies;

#define time_after(a,b)         ((long)(a) - (long)(b) > 0)
#define time_before(a,b)        time_after(b,a)
#define time_after_eq(a,b)      ((long)(a) - (long)(b) >= 0)
#define time_before_eq(a,b)     time_after_eq(b,a)

#define msecs_to_jiffies(x) \
	((x + (1000 / HZ) - 1) / (1000 / HZ))

#define jiffies_to_msecs(x) \
	((1000 / HZ) * x)

void msleep(int msec);

#endif
