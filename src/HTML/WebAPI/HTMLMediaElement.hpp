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
#ifndef SRC_HTML_WEBAPI_HTMLMEDIAELEMENT_HPP_
#define SRC_HTML_WEBAPI_HTMLMEDIAELEMENT_HPP_


namespace HTML {
namespace WebAPI {

enum CanPlayTypeResult { "" /* empty string */, "maybe", "probably" };
typedef (MediaStream or MediaSource or Blob) MediaProvider;


class HTMLMediaElement : HTMLElement {

  // error state
  const MediaError? error;

  // network state
    USVString src;
   MediaProvider? srcObject;
  const USVString currentSrc;
    DOM::DOMString? crossOrigin;
  const unsigned short NETWORK_EMPTY = 0;
  const unsigned short NETWORK_IDLE = 1;
  const unsigned short NETWORK_LOADING = 2;
  const unsigned short NETWORK_NO_SOURCE = 3;
  const unsigned short networkState;
    DOM::DOMString preload;
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
  const unrestricted double duration;
  object getStartDate();
  const bool paused;
   double defaultPlaybackRate;
   double playbackRate;
  const TimeRanges played;
  const TimeRanges seekable;
  const bool ended;
    bool autoplay;
    bool loop;
  Promise<void> play();
  void pause();

  // controls
    bool controls;
   double volume;
   bool muted;
    bool defaultMuted;

  // tracks
  [SameObject] const AudioTrackList audioTracks;
  [SameObject] const VideoTrackList videoTracks;
  [SameObject] const TextTrackList textTracks;
  TextTrack addTextTrack(TextTrackKind kind, optional DOM::DOMString label = "", optional DOM::DOMString language = "");
};

} /* namespace WebAPI */
} /* namespace HTML */


#endif /* SRC_HTML_WEBAPI_HTMLMEDIAELEMENT_HPP_ */

