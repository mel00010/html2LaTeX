/*******************************************************************************
 * CanvasRenderingContext2D.hpp
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
#ifndef SRC_HTML_DOM_CANVASRENDERINGCONTEXT2D_HPP_
#define SRC_HTML_DOM_CANVASRENDERINGCONTEXT2D_HPP_

#include "DOMString.hpp"
#include "HTMLCanvasElement.hpp"
#include "HTMLImageElement.hpp"
#include "HTMLVideoElement.hpp"
#include "ImageBitmap.hpp"
#include "OffscreenCanvas.hpp"

#include <list>
#include <optional>
#include <variant>

namespace HTML {
namespace DOM {

/* Forward Declares */

struct CanvasRenderingContext2DSettings;
class CanvasRenderingContext2D;
class CanvasState;
class CanvasTransform;
class CanvasCompositing;
class CanvasImageSmoothing;
class CanvasFillStrokeStyles;
class CanvasShadowStyles;
class CanvasFilters;
class CanvasRect;
class CanvasDrawPath;
class CanvasUserInterface;
class CanvasText;
class CanvasDrawImage;
class CanvasImageData;
class CanvasPathDrawingStyles;
class CanvasTextDrawingStyles;
class CanvasPath;
class CanvasGradient;
class CanvasPattern;
class TextMetrics;
class ImageData;
class Path2D;

typedef std::variant<HTMLImageElement, SVGImageElement> HTMLOrSVGImageElement;

typedef std::variant<HTMLOrSVGImageElement, HTMLVideoElement, HTMLCanvasElement, ImageBitmap, OffscreenCanvas> CanvasImageSource;

enum class CanvasFillRule {
	NON_ZERO, EVEN_ODD
};

struct CanvasRenderingContext2DSettings {
	public:
		bool alpha = true;
};

enum class ImageSmoothingQuality {
	LOW, MEDIUM, HIGH
};

class CanvasRenderingContext2D: public CanvasState,
		public CanvasTransform,
		public CanvasCompositing,
		public CanvasImageSmoothing,
		public CanvasFillStrokeStyles,
		public CanvasFilters,
		public CanvasRect,
		public CanvasDrawPath,
		public CanvasUserInterface,
		public CanvasText,
		public CanvasDrawImage,
		public CanvasImageData,
		public CanvasPathDrawingStyles,
		public CanvasTextDrawingStyles,
		public CanvasPath {
	public:
		// back-reference to the canvas
		const HTMLCanvasElement canvas;
};

/* Mixin */
class CanvasState {
	public:
		// state
		void save(); // push state on state stack
		void restore(); // pop state stack and restore state
};

/* Mixin */
class CanvasTransform {
	public:
		// transformations (default transform is the identity matrix)
		void scale(double x, double y);
		void rotate(double angle);
		void translate(double x, double y);
		void transform(double a, double b, double c, double d, double e, double f);

		DOMMatrix getTransform();
		void setTransform(double a, double b, double c, double d, double e, double f);
		void setTransform(std::optional<DOMMatrix2DInit> transform);
		void resetTransform();

};

/* Mixin */
class CanvasCompositing {
	public:
		// compositing
		double globalAlpha; // (default 1.0)
		DOMString globalCompositeOperation; // (default source-over)
};

/* Mixin */
class CanvasImageSmoothing {
	public:
		// image smoothing
		bool imageSmoothingEnabled; // (default true)
		ImageSmoothingQuality imageSmoothingQuality; // (default low)

};

/* Mixin */
class CanvasFillStrokeStyles {
	public:
		// colors and styles (see also the CanvasPathDrawingStyles and CanvasTextDrawingStyles interfaces)
		std::variant<DOMString, CanvasGradient, CanvasPattern> strokeStyle; // (default black)
		std::variant<DOMString, CanvasGradient, CanvasPattern> fillStyle; // (default black)
		CanvasGradient createLinearGradient(double x0, double y0, double x1, double y1);
		CanvasGradient createRadialGradient(double x0, double y0, double r0, double x1, double y1, double r1);
		std::optional<CanvasPattern> createPattern(CanvasImageSource image, DOMString repetition);

};

/* Mixin */
class CanvasShadowStyles {
	public:
		// shadows
		double shadowOffsetX; // (default 0)
		double shadowOffsetY; // (default 0)
		double shadowBlur; // (default 0)
		DOMString shadowColor; // (default transparent black)
};

/* Mixin */
class CanvasFilters {
	public:
		// filters
		DOMString filter; // (default "none")
};

/* Mixin */
class CanvasRect {
	public:
		// rects
		void clearRect(double x, double y, double w, double h);
		void fillRect(double x, double y, double w, double h);
		void strokeRect(double x, double y, double w, double h);
};

/* Mixin */
class CanvasDrawPath {
	public:
		// path API (see also CanvasPath)
		void beginPath();
		void fill(CanvasFillRule fillRule = CanvasFillRule::NON_ZERO);
		void fill(Path2D path, CanvasFillRule fillRule = CanvasFillRule::NON_ZERO);
		void stroke();
		void stroke(Path2D path);
		void clip(CanvasFillRule fillRule = CanvasFillRule::NON_ZERO);
		void clip(Path2D path, CanvasFillRule fillRule = CanvasFillRule::NON_ZERO);
		void resetClip();
		bool isPointInPath(double x, double y, CanvasFillRule fillRule = CanvasFillRule::NON_ZERO);
		bool isPointInPath(Path2D path, double x, double y, CanvasFillRule fillRule = CanvasFillRule::NON_ZERO);
		bool isPointInStroke(double x, double y);
		bool isPointInStroke(Path2D path, double x, double y);
};

/* Mixin */
class CanvasUserInterface {
	public:
		void drawFocusIfNeeded(Element element);
		void drawFocusIfNeeded(Path2D path, Element element);
		void scrollPathIntoView();
		void scrollPathIntoView(Path2D path);
};

/* Mixin */
class CanvasText {
	public:
		// text (see also the CanvasPathDrawingStyles and CanvasTextDrawingStyles interfaces)
		void fillText(DOMString text, double x, double y, std::optional<double> maxWidth);
		void strokeText(DOMString text, double x, double y, std::optional<double> maxWidth);
		TextMetrics measureText(DOMString text);
};

/* Mixin */
class CanvasDrawImage {
	public:
		// drawing images
		void drawImage(CanvasImageSource image, double dx, double dy);
		void drawImage(CanvasImageSource image, double dx, double dy, double dw, double dh);
		void drawImage(CanvasImageSource image, double sx, double sy, double sw, double sh, double dx, double dy, double dw, double dh);
};

/* Mixin */
class CanvasImageData {
	public:
		// pixel manipulation
		ImageData createImageData(long sw, long sh);
		ImageData createImageData(ImageData imagedata);
		ImageData getImageData(long sx, long sy, long sw, long sh);
		void putImageData(ImageData imagedata, long dx, long dy);
		void putImageData(ImageData imagedata, long dx, long dy, long dirtyX, long dirtyY, long dirtyWidth, long dirtyHeight);
};

enum class CanvasLineCap {
	BUTT, ROUND, SQUARE
};
enum class CanvasLineJoin {
	ROUND, BEVEL, MITER
};
enum class CanvasTextAlign {
	START, END, LEFT, RIGHT, CENTER
};
enum class CanvasTextBaseline {
	TOP, HANGING, MIDDLE, ALPHABETIC, IDEOGRAPHIC, BOTTOM
};
enum class CanvasDirection {
	LTR, RTL, INHERIT
};

/* Mixin */
class CanvasPathDrawingStyles {
	public:
		// line caps/joins
		double lineWidth; // (default 1)
		CanvasLineCap lineCap; // (default "butt")
		CanvasLineJoin lineJoin; // (default "miter")
		double miterLimit; // (default 10)

		// dashed lines
		void setLineDash(std::list<double> segments); // default empty
		std::list<double> getLineDash();
		double lineDashOffset;
};

/* Mixin */
class CanvasTextDrawingStyles {
	public:
		// text
		DOMString font; // (default 10px sans-serif)
		CanvasTextAlign textAlign; // (default: "start")
		CanvasTextBaseline textBaseline; // (default: "alphabetic")
		CanvasDirection direction; // (default: "inherit")
};

/* Mixin */
class CanvasPath {
	public:
		// shared path API methods
		void closePath();
		void moveTo(double x, double y);
		void lineTo(double x, double y);
		void quadraticCurveTo(double cpx, double cpy, double x, double y);
		void bezierCurveTo(double cp1x, double cp1y, double cp2x, double cp2y, double x, double y);
		void arcTo(double x1, double y1, double x2, double y2, double radius);
		void rect(double x, double y, double w, double h);
		void arc(double x, double y, double radius, double startAngle, double endAngle, bool anticlockwise = false);
		void ellipse(double x, double y, double radiusX, double radiusY, double rotation, double startAngle, double endAngle, bool anticlockwise = false);
};

class CanvasGradient {
	public:
		// opaque object
		void addColorStop(double offset, DOMString color);
};

class CanvasPattern {
	public:
// opaque object
		void setTransform(std::optional<DOMMatrix2DInit> transform);
};

class TextMetrics {
	public:
		// x-direction
		const double width; // advance width
		const double actualBoundingBoxLeft;
		const double actualBoundingBoxRight;

		// y-direction
		const double fontBoundingBoxAscent;
		const double fontBoundingBoxDescent;
		const double actualBoundingBoxAscent;
		const double actualBoundingBoxDescent;
		const double emHeightAscent;
		const double emHeightDescent;
		const double hangingBaseline;
		const double alphabeticBaseline;
		const double ideographicBaseline;
};

class ImageData {
	public:
		ImageData(unsigned long sw, unsigned long sh);
		ImageData(Uint8ClampedArray data, unsigned long sw, std::optional<unsigned long> sh);
		const unsigned long width;
		const unsigned long height;
		const Uint8ClampedArray data;
};

class Path2D: public CanvasPath {
	public:
		Path2D(Path2D path);
		Path2D(DOMString path);
		void addPath(Path2D path, std::optional<DOMMatrix2DInit> transform);
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_CANVASRENDERINGCONTEXT2D_HPP_ */

