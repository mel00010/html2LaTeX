/*******************************************************************************
 * TextTrack.hpp
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
#ifndef SRC_HTML_WEBAPI_TEXTTRACK_HPP_
#define SRC_HTML_WEBAPI_TEXTTRACK_HPP_

#include "EventHandler.hpp"
#include "TextTrackCue.hpp"
#include "TextTrackCueList.hpp"

#include <optional>

#include "../DOM/DOMString.hpp"

namespace HTML {
namespace WebAPI {

enum TextTrackMode {
	DISABLED, HIDDEN, SHOWING
};
enum TextTrackKind {
	SUBTITLES, CAPTIONS, DESCRIPTIONS, CHAPTERS, METADATA
};

class TextTrack: public DOM::EventTarget {
	public:
		const TextTrackKind kind;
		const DOM::DOMString label;
		const DOM::DOMString language;

		const DOM::DOMString id;
		const DOM::DOMString inBandMetadataTrackDispatchType;

		TextTrackMode mode;

		const std::optional<TextTrackCueList> cues;
		const std::optional<TextTrackCueList> activeCues;

		void addCue(TextTrackCue cue);
		void removeCue(TextTrackCue cue);

		EventHandler oncuechange;
};

} /* namespace WebAPI */
} /* namespace HTML */

#endif /* SRC_HTML_WEBAPI_TEXTTRACK_HPP_ */

