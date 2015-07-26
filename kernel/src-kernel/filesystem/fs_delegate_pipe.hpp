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

#ifndef GHOST_FILESYSTEM_FILESYSTEMRAMDISKPIPE
#define GHOST_FILESYSTEM_FILESYSTEMRAMDISKPIPE

#include "ghost/stdint.h"
#include "filesystem/fs_delegate.hpp"
#include "tasking/tasking.hpp"
#include "memory/contextual.hpp"

/**
 *
 */
class g_fs_delegate_pipe: public g_fs_delegate {
public:
	/**
	 *
	 */
	virtual ~g_fs_delegate_pipe() {
	}

	/**
	 *
	 */
	virtual g_fs_transaction_id request_discovery(g_thread* requester, g_fs_node* parent, char* child, g_fs_transaction_handler_discovery* handler);

	/**
	 *
	 */
	virtual void finish_discovery(g_thread* requester, g_fs_transaction_handler_discovery* handler);

	/**
	 *
	 */
	virtual g_fs_transaction_id request_read(g_thread* requester, g_fs_node* node, int64_t length, g_contextual<uint8_t*> buffer, g_file_descriptor_content* fd,
			g_fs_transaction_handler_read* handler);

	/**
	 *
	 */
	virtual void finish_read(g_thread* requester, g_fs_read_status* out_status, int64_t* out_result, g_file_descriptor_content* fd);

	/**
	 *
	 */
	virtual g_fs_transaction_id request_write(g_thread* requester, g_fs_node* node, int64_t length, g_contextual<uint8_t*> buffer,
			g_file_descriptor_content* fd, g_fs_transaction_handler_write* handler);

	/**
	 *
	 */
	virtual void finish_write(g_thread* requester, g_fs_write_status* out_status, int64_t* out_result, g_file_descriptor_content* fd);

	/**
	 *
	 */
	virtual g_fs_transaction_id request_get_length(g_thread* requester, g_fs_node* node, g_fs_transaction_handler_get_length* handler);

	/**
	 *
	 */
	virtual void finish_get_length(g_thread* requester, g_fs_transaction_handler_get_length* handler);

	/**
	 *
	 */
	virtual g_fs_transaction_id request_read_directory(g_thread* requester, g_fs_node* node, int position, g_fs_transaction_handler_read_directory* handler);

	/**
	 *
	 */
	virtual void finish_read_directory(g_thread* requester, g_fs_transaction_handler_read_directory* handler);

};

#endif
