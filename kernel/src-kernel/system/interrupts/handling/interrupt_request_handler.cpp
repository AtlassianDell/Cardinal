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

#include <system/interrupts/handling/interrupt_request_handler.hpp>
#include <logger/logger.hpp>
#include <system/io_ports.hpp>
#include <tasking/tasking.hpp>
#include <system/interrupts/pic.hpp>
#include <calls/syscall_handler.hpp>
#include <system/system.hpp>
#include <system/interrupts/ioapic_manager.hpp>
#include <memory/address_space.hpp>
#include <system/interrupts/ioapic.hpp>
#include <system/interrupts/ioapic_manager.hpp>

#include <tasking/tasking.hpp>
#include <tasking/thread_manager.hpp>
#include <tasking/wait/waiter_join.hpp>

/**
 * Map denoting which IRQs have happened and should be handled.
 */
bool irqsWaiting[256] = { };
g_irq_handler* handlers[256] = { };

/**
 * Performs interrupt request handling.
 */
g_processor_state* g_interrupt_request_handler::handle(g_processor_state* cpuState) {

	const uint32_t irq = cpuState->intr - 0x20;

	if (cpuState->intr == 0x80) {
		/*
		 System call
		 ===========
		 If the interrupt request is a system call, its handled by the system
		 call handler.
		 */
		cpuState = g_syscall_handler::handle(cpuState);

	} else if (irq == 0xFF) {
		/**
		 * Spurious interrupt
		 */
		g_log_warn("%! spurious interrupt was caught", "requests");

	} else if (irq == 0) {
		/*
		 Timer request
		 =============
		 Scheduler is called. The milliseconds are updated separately, because the
		 method to switch tasks may be called arbitrarily and is not guaranteed to be
		 called only on IRQ 0.
		 */
		g_tasking::getCurrentScheduler()->updateMilliseconds();
		cpuState = g_tasking::schedule(cpuState);

	} else if (irq < 256) {
		/*
		 IRQ handling
		 ============
		 These requests are stored in the map of waiting IRQs. The IRQ is masked so it
		 doesnt happen again before it has been handled.
		 */

		auto handler = handlers[irq];
		if (handler) {
			g_thread* thread = g_tasking::getTaskById(handler->thread_id);
			if (thread != nullptr) {
				// let the thread enter the irq handler
				thread->enter_irq_handler(handler->handler, irq, handler->callback);
				// it could be the current thread, so we have to switch
				cpuState = g_tasking::schedule(cpuState);
			}

		} else {
			// Mark the IRQ and mask it
			irqsWaiting[irq] = true;
		}

		// TODO this dies in VMWare: IOAPICManager::maskIrq(irq);

	} else {
		g_log_warn("%! unhandled irq %i", "requests", irq);
	}

	return cpuState;
}

/**
 * 
 */
bool g_interrupt_request_handler::pollIrq(uint8_t irq) {

	if (irqsWaiting[irq]) {

		irqsWaiting[irq] = false;

		// TODO this dies in VMWare: IOAPICManager::unmaskIrq(irq);

		return true;
	}

	return false;
}

/**
 *
 */
void g_interrupt_request_handler::set_handler(uint8_t irq, g_tid thread_id, uintptr_t handler_addr, uintptr_t callback_addr) {

	if (handlers[irq]) {
		delete handlers[irq];
	}

	g_irq_handler* handler = new g_irq_handler;
	handler->thread_id = thread_id;
	handler->handler = handler_addr;
	handler->callback = callback_addr;
	handlers[irq] = handler;
}

