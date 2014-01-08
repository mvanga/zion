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
#include <zion/ctype.h>

unsigned long strtoul(const char *cp,char **endp,unsigned int base)
{
	unsigned long result = 0,value;

	if (*cp == '0') {
		cp++;
		if ((*cp == 'x') && isxdigit(cp[1])) {
			base = 16;
			cp++;
		}
		if (!base) {
			base = 8;
		}
	}

	if (!base) {
		base = 10;
	}

	while (isxdigit(*cp) && (value = isdigit(*cp) ? *cp-'0' : (islower(*cp)
	    ? toupper(*cp) : *cp)-'A'+10) < base) {
		result = result*base + value;
		cp++;
	}

	if (endp)
		*endp = (char *)cp;

	return result;
}

long strtol(const char *cp,char **endp,unsigned int base)
{
	if(*cp=='-')
		return -strtoul(cp+1,endp,base);
	return strtoul(cp,endp,base);
}

int ustrtoul(const char *cp, char **endp, unsigned int base)
{
	unsigned long result = strtoul(cp, endp, base);

	switch (**endp) {
	case 'G' :
		result *= 1024;
		/* fall through */
	case 'M':
		result *= 1024;
		/* fall through */
	case 'K':
	case 'k':
		result *= 1024;
		if ((*endp)[1] == 'i') {
			if ((*endp)[2] == 'B')
				(*endp) += 3;
			else
				(*endp) += 2;
		}
	}

	return result;
}
