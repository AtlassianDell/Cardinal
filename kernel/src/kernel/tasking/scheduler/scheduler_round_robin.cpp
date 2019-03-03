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

#include "kernel/tasking/scheduler.hpp"
#include "kernel/memory/heap.hpp"
#include "shared/logger/logger.hpp"

void schedulerSchedule(g_tasking_local* local)
{
	if(!local->current)
	{
		local->current = local->list->task;
		return;
	}

	// Find current task in list
	g_task_entry* entry = local->list;
	while(entry)
	{
		if(entry->task == local->current)
		{
			break;
		}
		entry = entry->next;
	}
	if(!entry)
	{
		entry = local->list;
	}

	bool switched = false;
	int max = local->taskCount;
	while(max-- > 0)
	{
		// Select next in list
		entry = entry->next;
		if(!entry)
		{
			entry = local->list;
		}

		// Check task status
		g_task* task = entry->task;
		if(task->status == G_THREAD_STATUS_RUNNING)
		{

			// Can go there
			local->current = task;
			switched = true;
			break;
		}

		// Check wait resolver for waiting tasks
		if(task->status == G_THREAD_STATUS_WAITING && task->waitResolver && task->waitResolver(task))
		{
			// Wake task again
			task->status = G_THREAD_STATUS_RUNNING;
			task->waitResolver = 0;

			// Free wait data if necessary
			if(task->waitData)
			{
				heapFree((void*) task->waitData);
				task->waitData = 0;
			}

			local->current = task;
			switched = true;
			break;
		}
	}

	// Could not schedule, do idle
	if(!switched)
	{
		local->current = local->idleTask;
		logInfo("idle!");
	}
}
