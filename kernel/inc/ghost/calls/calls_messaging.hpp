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

#ifndef GHOST_API_CALLS_MESSAGING_CALLS
#define GHOST_API_CALLS_MESSAGING_CALLS

#include "ghost/ipc.h"

/**
 * @field taskId
 * 		the task id of the target task
 *
 * @field message
 * 		the message to send
 *
 * @field sendResult
 * 		the result of sending
 *
 * @security-level APPLICATION
 */
typedef struct {
	uint32_t taskId;
	g_message* message;

	g_message_send_status sendResult;
}__attribute__((packed)) g_syscall_send_msg;

/**
 * @field taskId
 * 		the task id which's messages should be received
 *
 * @field message
 * 		the message to write to
 *
 * @security-level APPLICATION
 */
typedef struct {
	uint32_t taskId;
	g_message* message;
	g_message_receive_mode mode;

	g_message_receive_status receiveResult;
}__attribute__((packed)) g_syscall_recv_msg;

/**
 * @field taskId
 * 		the task id which's messages should be received
 *
 * @field message
 * 		the message to write to
 *
 * @field topic
 * 		the topic to read from
 *
 * @security-level APPLICATION
 */
typedef struct {
	uint32_t taskId;
	g_message* message;
	uint32_t topic;
	g_message_receive_mode mode;

	g_message_receive_status receiveResult;
}__attribute__((packed)) g_syscall_recv_topic_msg;

/**
 * @field receiver
 * 		task id of the target task
 *
 * @field buffer
 * 		message buffer
 *
 * @field length
 * 		message length
 *
 * @field mode
 * 		sending mode
 *
 * @field status
 * 		one of the {g_message_send_status} codes
 *
 * @security-level APPLICATION
 */
typedef struct {
	g_tid receiver;
	void* buffer;
	size_t length;
	g_message_send_mode mode;
	g_message_transaction transaction;

	g_message_send_status status;
}__attribute__((packed)) g_syscall_send_message;

/**
 * @field buffer
 * 		target buffer
 *
 * @field maximum
 * 		buffer maximum length
 *
 * @field mode
 *		receiving mode
 *
 * @field transaction
 * 		transaction id or {G_MESSAGE_TRANSACTION_NONE}
 *
 * @field status
 * 		one of the {g_message_receive_status} codes
 *
 * @field break_condition
 * 		when giving, the receiving will wait no more
 * 		once the condition is true
 *
 * @security-level APPLICATION
 */
typedef struct {
	g_message_header* buffer;
	size_t maximum;
	g_message_receive_mode mode;
	g_message_transaction transaction;
	uint8_t* break_condition;

	g_message_receive_status status;
}__attribute__((packed)) g_syscall_receive_message;

#endif
