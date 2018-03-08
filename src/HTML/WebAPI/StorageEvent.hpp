/*******************************************************************************
 * StorageEvent.hpp
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
#ifndef SRC_HTML_WEBAPI_STORAGEEVENT_HPP_
#define SRC_HTML_WEBAPI_STORAGEEVENT_HPP_

#include "Storage.hpp"

#include <optional>

#include "../DOM/DOMString.hpp"
#include "../DOM/Event.hpp"
#include "../DOM/USVString.hpp"

namespace HTML {
namespace WebAPI {

struct StorageEventInit;

class StorageEvent: DOM::Event {
	public:
		StorageEvent(DOM::DOMString type);
		StorageEvent(DOM::DOMString type, StorageEventInit eventInitDict);

		const std::optional<DOM::DOMString> key;
		const std::optional<DOM::DOMString> oldValue;
		const std::optional<DOM::DOMString> newValue;
		const DOM::USVString url;
		const std::optional<Storage> storageArea;
};

struct StorageEventInit: public DOM::EventInit {
	public:
		std::optional<DOM::DOMString> key = std::nullopt;
		std::optional<DOM::DOMString> oldValue = std::nullopt;
		std::optional<DOM::DOMString> newValue = std::nullopt;
		DOM::USVString url = "";
		std::optional<Storage> storageArea = std::nullopt;
};

}
/* namespace WebAPI */
} /* namespace HTML */

#endif /* SRC_HTML_WEBAPI_STORAGEEVENT_HPP_ */

