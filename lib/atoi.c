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

#include <zion/stdlib.h>

int atoi(const char* s)
{
	long int v = 0;
	int sign = 1;

	while (*s == ' ' || (unsigned int)(*s - 9) < 5u)
		s++;

	switch (*s) {
		case '-': sign=-1;
		case '+': ++s;
	}

	while ((unsigned int)(*s - '0') < 10u) {
		v = v * 10 + *s - '0';
		++s;
	}

	return sign * v;
}
