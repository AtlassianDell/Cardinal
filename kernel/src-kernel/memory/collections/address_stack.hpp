/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *  Ghost, a micro-kernel based operating system for the x86 architecture    *
 *  Copyright (C) 2015, Max Schlüssel <lokoxe@gmail.com>                     *
 *                                                                           *
 *  This program is free software: you can redistribute it and/or modify     *
 *  it under the terms of the GNU General Public License as published by     *
 *  the Free Software Foundation, either version 3 of the License, or        *
 *  (at your option) any later version.                                      *
 *                                                                           *
 *  This program is distributed in the hope that it will be useful,          *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *  GNU General Public License for more details.                             *
 *                                                                           *
 *  You should have received a copy of the GNU General Public License        *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.    *
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef GHOST_MEMORY_ADDRESS_STACK
#define GHOST_MEMORY_ADDRESS_STACK

#include "ghost/stdint.h"
#include <memory/paging.hpp>
#include <memory/memory.hpp>

#define ADDRESS_STACK_CHUNK_ENTRIES		128

/**
 *
 */
struct g_address_stack_chunk {
	g_address_stack_chunk* previous;
	g_address_stack_chunk* next;
	g_address entries[ADDRESS_STACK_CHUNK_ENTRIES];
};

/**
 *
 */
class g_address_stack {
private:
	g_address_stack_chunk* current;
	uint32_t position;

public:
	g_address_stack();

	void push(g_address address);
	g_address pop();
};

#endif
