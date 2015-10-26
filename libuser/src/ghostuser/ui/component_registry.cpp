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

#include <ghostuser/ui/component_registry.hpp>
#include <ghostuser/ui/component.hpp>
#include <ghostuser/tasking/lock.hpp>
#include <map>

static g_lock components_lock;
static std::map<g_ui_component_id, g_component*> components;

/**
 *
 */
void g_component_registry::add(g_component* component) {
	components_lock.lock();
	components[component->getId()] = component;
	components_lock.unlock();
}

/**
 *
 */
g_component* g_component_registry::get(g_ui_component_id id) {
	if (components.count(id) > 0) {
		components_lock.lock();
		g_component* component = components[id];
		components_lock.unlock();
		return component;
	}
	return 0;
}
