/*******************************************************************************
 * WebSocket.hpp
 * Copyright (C) 2018  Mel McCalla <melmccalla@gmail.com>
 *
 * This file is part of html2LaTeX.
 *
 * html2LaTeX is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * html2LaTeX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with html2LaTeX.  If not, see <http://www.gnu.org/licenses/>.
 *******************************************************************************/
#ifndef SRC_HTML_DOM_WEBSOCKET_HPP_
#define SRC_HTML_DOM_WEBSOCKET_HPP_

#include "ArrayBuffer.hpp"
#include "ArrayBufferView.hpp"
#include "Blob.hpp"
#include "DOMString.hpp"
#include "EventHandler.hpp"
#include "EventTarget.hpp"
#include "USVString.hpp"

#include <list>

namespace HTML {
namespace DOM {

enum class BinaryType {
	BLOB, ARRAYBUFFER
};

class WebSocket: EventTarget {
	public:
		WebSocket(USVString url, std::list<DOMString> protocols = { });
		const USVString url;

		// ready state
		const unsigned short CONNECTING = 0;
		const unsigned short OPEN = 1;
		const unsigned short CLOSING = 2;
		const unsigned short CLOSED = 3;
		const unsigned short readyState;
		const unsigned long long bufferedAmount;

		// networking
		EventHandler onopen;
		EventHandler onerror;
		EventHandler onclose;
		const DOMString extensions;
		const DOMString protocol;
		void close(unsigned short code, USVString reason);

		// messaging
		EventHandler onmessage;
		BinaryType binaryType;
		void send(USVString data);
		void send(Blob data);
		void send(ArrayBuffer data);
		void send(ArrayBufferView data);
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_WEBSOCKET_HPP_ */

