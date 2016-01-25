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

#include <ghost.h>
#include <ghostuser/ui/button.hpp>
#include <ghostuser/ui/properties.hpp>
#include <ghostuser/ui/interface_specification.hpp>

/**
 *
 */
g_button* g_button::create() {
	return createComponent<g_button, G_UI_COMPONENT_TYPE_BUTTON>();
}

/**
 *
 */
void g_button::setEnabled(bool enabled) {
	g_component::setBoolProperty(G_UI_PROPERTY_ENABLED, enabled);
}

/**
 *
 */
bool g_button::isEnabled() {
	bool enabled;
	g_component::getBoolProperty(G_UI_PROPERTY_ENABLED, &enabled);
	return enabled;
}
