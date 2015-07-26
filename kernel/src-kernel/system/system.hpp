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

#ifndef GHOST_SHARED_SYSTEM_SYSTEM
#define GHOST_SHARED_SYSTEM_SYSTEM

#include "ghost/stdint.h"
#include <system/cpu.hpp>

/**
 * System class for processor and interrupt controller handling
 */
class g_system {
public:

	/**
	 * Used on the BSP to initialize AP processors and interrupt controllers
	 *
	 * @param initialPageDirectoryPhysical	physical address of the initial page
	 * 				directory, used for AP startup
	 */
	static void initializeBsp(g_physical_address initialPageDirectoryPhysical);

	/**
	 * Used on the APs for initialization
	 */
	static void initializeAp();

	/**
	 *
	 */
	static g_cpu* getCpus();

	/**
	 *
	 */
	static uint32_t getCpuCount();

	/**
	 * Returns the identifier to use for core identification
	 */
	static uint32_t getCurrentCoreId();

	/**
	 * Creates a core
	 */
	static void createCpu(uint32_t apicId);

	/**
	 *
	 */
	static g_cpu* getCpu(uint32_t coreId);

};

#endif
