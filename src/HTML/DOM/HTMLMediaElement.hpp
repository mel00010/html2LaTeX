/*******************************************************************************
 * HTMLMediaElement.hpp
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
#ifndef SRC_HTML_DOM_HTMLMEDIAELEMENT_HPP_
#define SRC_HTML_DOM_HTMLMEDIAELEMENT_HPP_

#include "AudioTrackList.hpp"
#include "Blob.hpp"
#include "DOMString.hpp"
#include "HTMLElement.hpp"
#include "MediaError.hpp"
#include "TextTrack.hpp"
#include "TextTrackList.hpp"
#include "TimeRanges.hpp"
#include "USVString.hpp"
#include "VideoTrackList.hpp"

#include <any>
#include <future>
#include <optional>
#include <variant>

namespace HTML {
namespace DOM {

enum class CanPlayTypeResult {
	EMPTY, MAYBE, PROBABLY
};
//typedef std::variant<MediaStream, MediaSource, Blob> MediaProvider;
typedef std::variant<Blob> MediaProvider;


class HTMLMediaElement: public HTMLElement {
	public:
		// error state
		const std::optional<MediaError> error;

		// network state
		USVString src;
		std::optional<MediaProvider> srcObject;
		const USVString currentSrc;
		std::optional<DOMString> crossOrigin;
		const unsigned short NETWORK_EMPTY = 0;
		const unsigned short NETWORK_IDLE = 1;
		const unsigned short NETWORK_LOADING = 2;
		const unsigned short NETWORK_NO_SOURCE = 3;
		const unsigned short networkState;
		DOMString preload;
		const TimeRanges buffered;
		void load();
		CanPlayTypeResult canPlayType(DOMString type);

		// ready state
		const unsigned short HAVE_NOTHING = 0;
		const unsigned short HAVE_METADATA = 1;
		const unsigned short HAVE_CURRENT_DATA = 2;
		const unsigned short HAVE_FUTURE_DATA = 3;
		const unsigned short HAVE_ENOUGH_DATA = 4;
		const unsigned short readyState;
		const bool seeking;

		// playback state
		double currentTime;
		void fastSeek(double time);
		const double duration;
		std::any getStartDate();
		const bool paused;
		double defaultPlaybackRate;
		double playbackRate;
		const TimeRanges played;
		const TimeRanges seekable;
		const bool ended;
		bool autoplay;
		bool loop;
		std::promise<std::any> play();
		void pause();

		// controls
		bool controls;
		double volume;
		bool muted;
		bool defaultMuted;

		// tracks
	protected:
		const AudioTrackList audioTracks;
		const VideoTrackList videoTracks;
		const TextTrackList textTracks;

	public:
		TextTrack addTextTrack(TextTrackKind kind,
				std::optional<DOMString> label = U"",
				std::optional<DOMString> language = U"");
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_HTMLMEDIAELEMENT_HPP_ */

