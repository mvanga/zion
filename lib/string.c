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

#include <zion/string.h>

char *strcpy(char * d, char *s)
{
	char *res = d;

	while ((*d++ = *s++) != '\0')
		;
	return res;
}

int strlen(char *s)
{
	char *sc;

	for (sc = s; *sc != '\0'; ++sc)
		/* nothing */;
	return sc - s;
}

int strnlen(char *s, int count)
{
	char *sc;

	for (sc = s; count-- && *sc != '\0'; ++sc)
		/* nothing */;
	return sc - s;
}

void *memcpy(void *d, void *s, int count)
{
	unsigned long *dl = (unsigned long *)d, *sl = (unsigned long *)s;
	char *d8, *s8;

	/* while all data is aligned (common case), copy a word at a time */
	if ( (((unsigned long)d | (unsigned long)s) & (sizeof(*dl) - 1)) == 0) {
		while (count >= (int)sizeof(*dl)) {
			*dl++ = *sl++;
			count -= sizeof(*dl);
		}
	}
	/* copy the reset one byte at a time */
	d8 = (char *)dl;
	s8 = (char *)sl;
	while (count--)
		*d8++ = *s8++;

	return d;
}

void * memset(void *s, int c, int count)
{
	unsigned long *sl = (unsigned long *) s;
	unsigned long cl = 0;
	char *s8;
	int i;

	/* do it one word at a time (32 bits or 64 bits) while possible */
	if ( ((unsigned long)s & (sizeof(*sl) - 1)) == 0) {
		for (i = 0; i < (int)sizeof(*sl); i++) {
			cl <<= 8;
			cl |= c & 0xff;
		}
		while (count >= (int)sizeof(*sl)) {
			*sl++ = cl;
			count -= sizeof(*sl);
		}
	}
	/* fill 8 bits at a time */
	s8 = (char *)sl;
	while (count--)
		*s8++ = c;

	return s;
}

int strncmp(const char *s1, const char *s2, int n)
{
	unsigned char u1, u2;

	while (n-- > 0)
	{
		u1 = (unsigned char) *s1++;
		u2 = (unsigned char) *s2++;
		if (u1 != u2)
			return u1 - u2;
		if (u1 == '\0')
			return 0;
	}
	return 0;
}

char *strchr(const char *s, int c)
{
	do {
		if (*s == c)
		{
			return (char*)s;
		}
	} while (*s++);
	return (0);
}
