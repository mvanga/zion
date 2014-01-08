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

#include <zion/rand.h>
#include <zion/types.h>

/* Knuth's TAOCP section 3.6 */
#define	M	((1U<<31) -1)
#define	A	48271
#define	Q	44488		/* M/A */
#define	R	3399		/* M%A; R < Q !!! */

int rand_r(unsigned int* seed)
{
	int32_t X;

	X = *seed;
	X = A*(X%Q) - R * (int32_t) (X/Q);
	if (X < 0)
		X += M;

	*seed = X;
	return X;
}

static unsigned int seed = 1;

int rand(void)
{
	return rand_r(&seed);
}

void srand(unsigned int s)
{
	seed = s;
}

int random(void) __attribute__((alias("rand")));
void srandom(unsigned int i) __attribute__((alias("srand")));
