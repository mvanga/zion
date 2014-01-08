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

#include <zion/ctype.h>

inline int isdigit(int c)
{
	return c >= '0' && c <= '9';
}

inline int isxdigit(int c)
{
	return isdigit(c)
		|| (c >= 'a' && c <= 'f')
		|| (c >= 'A' && c <= 'F');
}

inline int isalpha(int c)
{
	return islower(c) || isupper(c);
}

inline int isalnum(int c)
{
	return isalpha(c) || isdigit(c);
}

inline int islower(int c)
{
    return c >= 'a' && c <= 'z';
}

inline int isupper(int c)
{
    return c >= 'A' && c <= 'Z';
}

inline int toupper(int c)
{
    if (!islower(c))
    	return c;
    return c - 'a' + 'A';
}

inline int tolower(int c)
{
	if (!isupper(c))
		return c;
	return c - 'A' + 'a';
}
