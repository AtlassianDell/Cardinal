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

#ifndef GHOSTLIBRARY_FILESYSTEM_FILEUTILS
#define GHOSTLIBRARY_FILESYSTEM_FILEUTILS

#include <stdint.h>
#include <sstream>

/**
 *
 */
class g_file_utils {
public:

	/**
	 *
	 */
	static bool read_string(g_fd fd, std::string& out);

	/**
	 *
	 */
	static bool read_bytes(g_fd fd, uint8_t* buffer, size_t len);

	/**
	 *
	 */
	static bool read_bytes(g_fd fd, size_t offset, uint8_t* arr, size_t count);

	static bool tryReadBytes(FILE* file, uint32_t offset, uint8_t* buffer,
			uint32_t len);
};

#endif
