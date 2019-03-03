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

#include "kernel/calls/syscall_general.hpp"

#include "kernel/memory/heap.hpp"
#include "shared/logger/logger.hpp"

struct g_syscall_sleep_wait_data
{
	uint64_t wakeTime;
};

bool syscallSleepWaitResolver(g_task* task)
{
	g_syscall_sleep_wait_data* waitData = (g_syscall_sleep_wait_data*) task->waitData;
	return taskingGetLocal()->time > waitData->wakeTime;
}

void syscallSleep(g_task* task, g_syscall_sleep* data)
{
	task->status = G_THREAD_STATUS_WAITING;
	task->waitResolver = syscallSleepWaitResolver;

	g_syscall_sleep_wait_data* waitData = (g_syscall_sleep_wait_data*) heapAllocate(sizeof(g_syscall_sleep_wait_data));
	waitData->wakeTime = taskingGetLocal()->time + data->milliseconds;
	task->waitData = waitData;

	taskingSchedule();
}
