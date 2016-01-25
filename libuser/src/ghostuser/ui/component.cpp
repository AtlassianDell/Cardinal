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
#include <ghostuser/ui/component.hpp>
#include <ghostuser/ui/interface_specification.hpp>
#include <ghostuser/utils/value_placer.hpp>

/**
 *
 */
bool g_component::addChild(g_component* child) {

	if (!g_ui_initialized) {
		return 0;
	}

	// send initialization request
	uint32_t tx = g_ipc_next_topic();

	g_ui_component_add_child_request request;
	request.header.id = G_UI_PROTOCOL_ADD_COMPONENT;
	request.parent = this->id;
	request.child = child->id;
	g_send_message_t(g_ui_delegate_tid, &request, sizeof(g_ui_component_add_child_request), tx);

	// read response
	size_t bufferSize = sizeof(g_message_header) + sizeof(g_ui_component_add_child_response);
	uint8_t buffer[bufferSize];

	if (g_receive_message_t(buffer, bufferSize, tx) == G_MESSAGE_RECEIVE_STATUS_SUCCESSFUL) {
		g_ui_component_add_child_response* response = (g_ui_component_add_child_response*) G_MESSAGE_CONTENT(buffer);
		if (response->status == G_UI_PROTOCOL_SUCCESS) {
			return true;
		}
	}

	return false;

}

/**
 *
 */
bool g_component::setBounds(g_rectangle rect) {

	if (!g_ui_initialized) {
		return 0;
	}

	// send initialization request
	uint32_t tx = g_ipc_next_topic();

	g_ui_component_set_bounds_request request;
	request.header.id = G_UI_PROTOCOL_SET_BOUNDS;
	request.id = this->id;
	request.bounds = rect;
	g_send_message_t(g_ui_delegate_tid, &request, sizeof(g_ui_component_set_bounds_request), tx);

	// read response
	size_t bufferSize = sizeof(g_message_header) + sizeof(g_ui_component_set_bounds_response);
	g_local<uint8_t> buffer(new uint8_t[bufferSize]);

	if (g_receive_message_t(buffer(), bufferSize, tx) == G_MESSAGE_RECEIVE_STATUS_SUCCESSFUL) {
		g_ui_component_set_bounds_response* response = (g_ui_component_set_bounds_response*) G_MESSAGE_CONTENT(buffer());

		if (response->status == G_UI_PROTOCOL_SUCCESS) {
			return true;
		}
	}

	return false;

}

/**
 *
 */
g_rectangle g_component::getBounds() {

	if (!g_ui_initialized) {
		return g_rectangle();
	}

	// send initialization request
	uint32_t tx = g_ipc_next_topic();

	g_ui_component_get_bounds_request request;
	request.header.id = G_UI_PROTOCOL_GET_BOUNDS;
	request.id = this->id;
	g_send_message_t(g_ui_delegate_tid, &request, sizeof(g_ui_component_get_bounds_request), tx);

	// read response
	size_t bufferSize = sizeof(g_message_header) + sizeof(g_ui_component_get_bounds_response);
	g_local<uint8_t> buffer(new uint8_t[bufferSize]);

	if (g_receive_message_t(buffer(), bufferSize, tx) == G_MESSAGE_RECEIVE_STATUS_SUCCESSFUL) {
		g_ui_component_get_bounds_response* response = (g_ui_component_get_bounds_response*) G_MESSAGE_CONTENT(buffer());

		if (response->status == G_UI_PROTOCOL_SUCCESS) {
			return response->bounds;
		}
	}

	return g_rectangle();

}

/**
 *
 */
bool g_component::setVisible(bool visible) {

	if (!g_ui_initialized) {
		return 0;
	}

	// send initialization request
	uint32_t tx = g_ipc_next_topic();

	g_ui_component_set_visible_request request;
	request.header.id = G_UI_PROTOCOL_SET_VISIBLE;
	request.id = this->id;
	request.visible = visible;
	g_send_message_t(g_ui_delegate_tid, &request, sizeof(g_ui_component_set_visible_request), tx);

	// read response
	size_t bufferSize = sizeof(g_message_header) + sizeof(g_ui_component_set_visible_response);
	uint8_t buffer[bufferSize];

	if (g_receive_message_t(buffer, bufferSize, tx) == G_MESSAGE_RECEIVE_STATUS_SUCCESSFUL) {
		g_ui_component_set_visible_response* response = (g_ui_component_set_visible_response*) G_MESSAGE_CONTENT(buffer);
		if (response->status == G_UI_PROTOCOL_SUCCESS) {
			return true;
		}
	}

	return false;

}

/**
 *
 */
bool g_component::setBoolProperty(int property, bool value) {

	if (!g_ui_initialized) {
		return false;
	}

	// send initialization request
	uint32_t tx = g_ipc_next_topic();

	g_ui_component_set_bool_property_request request;
	request.header.id = G_UI_PROTOCOL_SET_BOOL_PROPERTY;
	request.id = this->id;
	request.property = property;
	request.value = value;
	g_send_message_t(g_ui_delegate_tid, &request, sizeof(g_ui_component_set_bool_property_request), tx);

	// read response
	size_t bufferSize = sizeof(g_message_header) + sizeof(g_ui_component_set_bool_property_response);
	g_local<uint8_t> buffer(new uint8_t[bufferSize]);

	if (g_receive_message_t(buffer(), bufferSize, tx) == G_MESSAGE_RECEIVE_STATUS_SUCCESSFUL) {
		g_ui_component_set_bool_property_response* response = (g_ui_component_set_bool_property_response*) G_MESSAGE_CONTENT(buffer());

		if (response->status == G_UI_PROTOCOL_SUCCESS) {
			return true;
		}
	}

	return false;
}

/**
 *
 */
bool g_component::getBoolProperty(int property, bool* out) {

	if (!g_ui_initialized) {
		return false;
	}

	// send initialization request
	uint32_t tx = g_ipc_next_topic();

	g_ui_component_get_bool_property_request request;
	request.header.id = G_UI_PROTOCOL_GET_BOOL_PROPERTY;
	request.id = this->id;
	request.property = property;
	g_send_message_t(g_ui_delegate_tid, &request, sizeof(g_ui_component_get_bool_property_request), tx);

	// read response
	size_t bufferSize = sizeof(g_message_header) + sizeof(g_ui_component_get_bool_property_response);
	g_local<uint8_t> buffer(new uint8_t[bufferSize]);

	if (g_receive_message_t(buffer(), bufferSize, tx) == G_MESSAGE_RECEIVE_STATUS_SUCCESSFUL) {
		g_ui_component_get_bool_property_response* response = (g_ui_component_get_bool_property_response*) G_MESSAGE_CONTENT(buffer());

		if (response->status == G_UI_PROTOCOL_SUCCESS) {
			*out = response->value;
			return true;
		}
	}

	return false;
}

/**
 *
 */
bool g_component::setListener(g_ui_component_event_type eventType, g_listener* new_listener) {

	if (!g_ui_initialized) {
		return false;
	}

	// set new
	listeners[eventType] = new_listener;

	// check
	if (new_listener == 0) {
		return false;
	}

	// send request
	uint32_t tx = g_ipc_next_topic();

	g_ui_component_set_listener_request request;
	request.header.id = G_UI_PROTOCOL_SET_LISTENER;
	request.id = this->id;
	request.target_thread = g_ui_event_dispatcher_tid;
	request.event_type = eventType;
	g_send_message_t(g_ui_delegate_tid, &request, sizeof(g_ui_component_set_listener_request), tx);

	// read response
	size_t bufferSize = sizeof(g_message_header) + sizeof(g_ui_component_set_listener_response);
	uint8_t buffer[bufferSize];

	if (g_receive_message_t(buffer, bufferSize, tx) == G_MESSAGE_RECEIVE_STATUS_SUCCESSFUL) {
		g_ui_component_set_listener_response* response = (g_ui_component_set_listener_response*) G_MESSAGE_CONTENT(buffer);
		if (response->status == G_UI_PROTOCOL_SUCCESS) {
			return true;
		}
	}

	return false;
}

/**
 *
 */
void g_component::handle(g_ui_component_event_header* header) {

	auto eventType = header->type;
	g_listener* listener = listeners[eventType];

	if (listener != nullptr) {
		listener->process(header);
	}
}
