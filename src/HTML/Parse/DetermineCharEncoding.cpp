/*******************************************************************************
 * DetermineCharEncoding.cpp
 * Copyright (C) 2017  Mel McCalla <melmccalla@gmail.com>
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

#include <HTML/Parse/DetermineCharEncoding.hpp>
#include <HTML/Parse/MagicString.hpp>
#include <HTML/Microsyntaxes/ASCII.hpp>
#include <HTML/HTMLTypes.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>

#include <vector>

#include <gtest/gtest.h>



/**
 * @file  HTML/Parse/DetermineCharEncoding.cpp
 * @brief Implements HTML/Parse/DetermineCharEncoding.hpp
 */
namespace HTML {
namespace Parse {



ContentType DetermineCharEncoding::determineCharEncoding(std::istream& input) {
	ContentType encoding;

	input.exceptions(std::istream::eofbit);

	try {
		encoding = tryUnicodeBOM(input);
		if (encoding.charEncoding != UNKNOWN) {
			input.seekg(0);
			return encoding;
		}

		encoding = preScan(input);
		if (encoding.charEncoding != UNKNOWN) {
			input.seekg(0);
			return encoding;
		}
	}
	catch (std::istream::failure& e) {
		std::cerr << "Error: Reached end of file before determining character encoding. " << std::endl;
		throw;
	}
	catch (...) {
		throw;
	}
	input.seekg(0);
	return encoding;
}

ContentType DetermineCharEncoding::tryUnicodeBOM(std::istream& input) {
	ContentType encoding;
	Byte buffer[3] = { 0 };

	input.read((char*) buffer, 3);
	input.clear();
	input.seekg(0);
	if ((buffer[0] == MagicString::UnicodeBOM::UTF_16_BE[0]) && (buffer[1] == MagicString::UnicodeBOM::UTF_16_BE[1])) {
		encoding.charEncoding = UTF_16_BE;
		encoding.confidence = CERTAIN;
		return encoding;
	} else if ((buffer[0] == MagicString::UnicodeBOM::UTF_16_LE[0]) && (buffer[1] == MagicString::UnicodeBOM::UTF_16_LE[1])) {
		encoding.charEncoding = UTF_16_LE;
		encoding.confidence = CERTAIN;
		return encoding;
	} else if ((buffer[0] == MagicString::UnicodeBOM::UTF_8[0]) && (buffer[1] == MagicString::UnicodeBOM::UTF_8[1])
			&& (buffer[2] == MagicString::UnicodeBOM::UTF_8[2])) {
		encoding.charEncoding = UTF_8;
		encoding.confidence = CERTAIN;
		return encoding;
	}
	return encoding;
}

ContentType DetermineCharEncoding::preScan(std::istream& input) {
	ContentType encoding;

	input.exceptions(std::istream::eofbit);
	try {
		while (true) {
			input.seekg(1, input.cur);
			encoding = commentTagAlgorithm(input);
			if (encoding.charEncoding != UNKNOWN) {
				return encoding;
			}

			encoding = metaTagAlgorithm(input);
			if (encoding.charEncoding != UNKNOWN) {
				return encoding;
			}

			encoding = asciiTagAlgorithm(input);
			if (encoding.charEncoding != UNKNOWN) {
				return encoding;
			}

			encoding = punctuationTagAlgorithm(input);
			if (encoding.charEncoding != UNKNOWN) {
				return encoding;
			}
		}
	}
	catch (...) {
		throw;
	}
	return encoding;
}

ContentType DetermineCharEncoding::commentTagAlgorithm(std::istream& input) {
	ContentType encoding;

	input.exceptions(std::istream::eofbit);
	try {
		Byte startBuffer[4] = { 0 };
		input.read((char*) startBuffer, 4);

		for (size_t i = 0; i < 4; i++) {
			if (startBuffer[i] != HTML::Parse::MagicString::CommentTag::start[i]) {
				input.seekg(-4, input.cur);
				return encoding;
			}
		}
		input.seekg(-3, input.cur);
	}
	catch (...) {
		throw;
	}

	try {

		while (true) {
			Byte endBuffer[3] = { 0 };
			input.read((char*) endBuffer, 3);
			bool breakLoop = true;
			for (size_t i = 0; i < 3; i++) {
				if (endBuffer[i] != HTML::Parse::MagicString::CommentTag::end[i]) {
					input.seekg(-2, input.cur);
					breakLoop = false;
					break;
				}

			}
			if (breakLoop) {
				break;
			}
		}
	}
	catch (...) {
		throw;
	}
	return encoding;
}

ContentType DetermineCharEncoding::metaTagAlgorithm(std::istream& input) {
	ContentType encoding;
	MagicString::MetaTag MetaTag;
	Byte buffer[6] = { 0 };

	input.exceptions(std::istream::eofbit);
	try {
		input.read((char*) buffer, 6);
		if (buffer != MetaTag) {
			input.seekg(-6, input.cur);
			return encoding;
		} else {
			input.seekg(-1, input.cur);
		}
	}
	catch (...) {
		throw;
	}

	try {
		std::vector<Attribute> attributeList;
		bool gotPragma = false;
		TriBool needPragma = NONE;
		CharEncoding charSet = NULL_ENC;
		while (true) {
			Attribute attribute;
			try {
				attribute = getAttribute(input);
			}
			catch (...) {
				break;
			}
			if (attribute == false) {
				break;
			} else {

				bool nameMatched = false;
				for (auto& i : attributeList) {
					if (i.name == attribute.name) {
						nameMatched = true;
						break;
					}
				}
				if (nameMatched) {
					continue;
				}

				attributeList.push_back(attribute);
				if (attributeList.back().name == "http-equiv") {
					if (attribute.value == "content-type") {
						gotPragma = true;
					}
				} else if (attributeList.back().name == "content") {
					CharEncoding enc = extractCharEncodingFromMetaTag(attributeList.back().value);
					if ((enc != NULL_ENC) && charSet == NULL_ENC) {
						needPragma = TRUE;
						charSet = enc;
					}
				} else if (attributeList.back().name == "charset") {
					CharEncoding enc = getCharEncodingFromString(attributeList.back().value);
					needPragma = FALSE;
					charSet = enc;
				}

			}
		}
		if (needPragma == NONE) {
			input.seekg(1, input.cur);
			return encoding;
		} else if ((needPragma == TRUE) && (gotPragma == false)) {
			input.seekg(1, input.cur);
			return encoding;
		} else if (charSet == UNKNOWN) {
			input.seekg(1, input.cur);
			return encoding;
		}

		if ((charSet == UTF_16_LE) || (charSet == UTF_16_BE)) {
			charSet = UTF_8;
		}
		encoding.charEncoding = charSet;
		encoding.confidence = TENTATIVE;
		return encoding;
	}
	catch (...) {
		throw;
	}
	return encoding;
}

ContentType DetermineCharEncoding::asciiTagAlgorithm(std::istream & input) {
	ContentType encoding;
	Byte buffer1[2] = { 0 };
	Byte buffer2[3] = { 0 };
	MagicString::ASCIITag ASCIITag;
	MagicString::ASCIIEndTag ASCIIEndTag;

	input.exceptions(std::istream::eofbit);
	try {
		input.read((char*) buffer1, 2);
		if (buffer1 != ASCIITag) {
			input.seekg(-2, input.cur);
			input.read((char*) buffer2, 3);
			if (buffer2 != ASCIIEndTag) {
				input.seekg(-3, input.cur);
				return encoding;
			}
		}
		Byte buf = 0x00;
		input.read((char *) &buf, 1);
		while (buf != 0x3E) {
			input.read((char *) &buf, 1);
		}
	}
	catch (...) {
		throw;
	}
	return encoding;
}
ContentType DetermineCharEncoding::punctuationTagAlgorithm(std::istream & input) {
	ContentType encoding;
	Byte buffer[2] = { 0 };
	MagicString::PunctuationTag PunctuationTag;

	input.exceptions(std::istream::eofbit);
	try {
		input.read((char*) buffer, 2);
		if (buffer == PunctuationTag) {
			Byte buf = 0x00;
			while (buf != 0x3E) {
				input.read((char *) &buf, 1);
			}
			input.seekg(1, input.cur);
		} else {
			input.seekg(-2, input.cur);
		}
	}
	catch (...) {
		throw;
	}
	return encoding;
}

Attribute DetermineCharEncoding::getAttribute(std::istream & input, bool swallowExceptions) {
	Attribute attribute;
	attribute.name = "";
	attribute.value = "";
	input.exceptions(std::istream::eofbit);
	Byte buf = 0x00;
	try {
		input.read((char *) &buf, 1);
		if ((buf == 0x09) || (buf == 0x0A) || (buf == 0x0C) || (buf == 0x0D) || (buf == 0x20) || (buf == 0x2F)) {
			while ((buf == 0x09) || (buf == 0x0A) || (buf == 0x0C) || (buf == 0x0D) || (buf == 0x20) || (buf == 0x2F)) {
				input.read((char *) &buf, 1);
			}
		}
		{
			if (buf == 0x3E) {
				return attribute;
			} else {
				while (true) {
					if ((buf == 0x3D) && !(attribute.name.empty())) {
						attribute.value = getAttributeValue(input, buf);
						return attribute;
					} else if ((buf == 0x2F) || (buf == 0x3E)) {
						return attribute;
					} else if ((buf == 0x09) || (buf == 0x0A) || (buf == 0x0C) || (buf == 0x0D) || (buf == 0x20)) {
						while ((buf == 0x09) || (buf == 0x0A) || (buf == 0x0C) || (buf == 0x0D) || (buf == 0x20)) {
							input.read((char *) &buf, 1);
						}
						if (buf != 0x3D) {
							return attribute;
						} else {
							attribute.value = getAttributeValue(input, buf);
							return attribute;
						}
					} else if (Microsyntaxes::isASCIIUpper(buf)) {
						Byte result = buf + 0x20;
						attribute.name.append((char*) &(result), 1);
						input.read((char*) &buf, 1);
					} else {
						attribute.name.append((char*) &buf, 1);
						input.read((char*) &buf, 1);
					}
				}
			}
		}
	}
	catch (...) {
		if (swallowExceptions) {
			return attribute;
		} else {
			throw;
		}
	}
	return attribute;
}
std::string DetermineCharEncoding::getAttributeValue(std::istream& input, Byte& buf) {
	std::string value = "";
	try {
		input.read((char*) &buf, 1);
		if ((buf == 0x09) || (buf == 0x0A) || (buf == 0x0C) || (buf == 0x0D) || (buf == 0x20)) {
			while ((buf == 0x09) || (buf == 0x0A) || (buf == 0x0C) || (buf == 0x0D) || (buf == 0x20)) {
				input.read((char *) &buf, 1);
			}
		}
		{
			if ((buf == 0x22) || (buf == 0x27)) {
				std::string value_ = quoteLoop(input, buf, value);
				return value_;
			} else if (buf == 0x3E) {
				return value;
			} else if (Microsyntaxes::isASCIIUpper(buf)) {
				Byte result = buf + 0x20;
				value.append((char*) &(result), 1);
				std::string value_ = processingLoop(input, buf, value);
				return value_;
			} else {
				value.append((char*) &(buf), 1);
				std::string value_ = processingLoop(input, buf, value);
				return value_;
			}
		}
	}
	catch (...) {
		return value;
	}
	return value;
}
std::string DetermineCharEncoding::processingLoop(std::istream& input, Byte& buf, std::string& value) {
	std::string localValue(value);
	try {
		while (true) {
			input.read((char*) &buf, 1);
			if ((buf == 0x09) || (buf == 0x0A) || (buf == 0x0C) || (buf == 0x0D) || (buf == 0x3E)) {
				return localValue;
			} else if (Microsyntaxes::isASCIIUpper(buf)) {
				Byte result = buf + 0x20;
				localValue.append((char*) &(result), 1);
			} else {
				localValue.append((char*) &(buf), 1);
			}
		}
	}
	catch (...) {
		return localValue;
	}
	return localValue;
}

std::string DetermineCharEncoding::quoteLoop(std::istream& input, Byte& buf, std::string& value) {
	std::string localValue(value);
	try {
		Byte b = buf;
		input.read((char *) &buf, 1);
		while (true) {
			if (buf == b) {
				return localValue;
			} else {
				if (Microsyntaxes::isASCIIUpper(buf)) {
					Byte result = buf + 0x20;
					localValue.append((char*) &(result), 1);
					input.read((char*) &buf, 1);
				} else {
					localValue.append((char*) &(buf), 1);
					input.read((char*) &buf, 1);
				}
			}
		}
	}
	catch (...) {
		return localValue;
	}
	return localValue;
}

CharEncoding DetermineCharEncoding::extractCharEncodingFromMetaTag(std::string & string) {
	CharEncoding encoding = NULL_ENC;
	std::stringstream input(string);
	input.exceptions(std::istream::eofbit);
	Byte buf = 0x00;
	std::string buffer;
	bool gotEndQuote = false;
	try {
		while (true) {
			Byte charsetBuf[7] = { 0 };
			for (size_t i = 0; i < string.size(); i++) {
				input.read((char *) charsetBuf, 7);
				if (MagicString::isCharset(charsetBuf)) {
					break;
				} else {
					input.seekg(-6, input.cur);
				}
			}
			if (!(MagicString::isCharset(charsetBuf))) {
				return encoding;
			}
			input.read((char*) &buf, 1);
			if ((buf == 0x09) || (buf == 0x0A) || (buf == 0x0C) || (buf == 0x0D) || (buf == 0x20)) {
				while ((buf == 0x09) || (buf == 0x0A) || (buf == 0x0C) || (buf == 0x0D) || (buf == 0x20)) {
					input.read((char *) &buf, 1);
				}
			}
			if (buf != 0x3D) {
				input.seekg(-1, input.cur);
			} else {
				break;
			}
		}
		input.read((char*) &buf, 1);
		if ((buf == 0x09) || (buf == 0x0A) || (buf == 0x0C) || (buf == 0x0D) || (buf == 0x20)) {
			while ((buf == 0x09) || (buf == 0x0A) || (buf == 0x0C) || (buf == 0x0D) || (buf == 0x20)) {
				input.read((char *) &buf, 1);
			}
		}

		size_t position = input.tellg();
		input.seekg(0, input.end);
		size_t bytesLeft = (size_t) input.tellg() - position;
		input.seekg(position);

		if (buf == '"') {
			for (size_t i = 0; i < bytesLeft; i++) {
				input.read((char *) &buf, 1);
				if (buf == '"') {
					gotEndQuote = true;
					break;
				} else {
					buffer.append((char*) &buf, 1);
				}
			}
			if (buffer.empty() || !gotEndQuote) {
				return encoding;
			}
		} else if (buf == '\'') {
			for (size_t i = 0; i < bytesLeft; i++) {
				input.read((char *) &buf, 1);
				if (buf == '\'') {
					gotEndQuote = true;
					break;
				} else {
					buffer.append((char*) &buf, 1);
				}
			}
			if (buffer.empty() || !gotEndQuote) {
				return encoding;
			}
		} else {
			for (size_t i = 0; i < bytesLeft + 1; i++) {
				if (buf == ' ' || buf == ';') {
					break;
				} else {
					buffer.append((char*) &buf, 1);
					input.read((char *) &buf, 1);
				}
			}
			if (buffer.empty()) {
				return encoding;
			}
		}
		encoding = getCharEncodingFromString(buffer);
		return encoding;
	}
	catch (...) {
		encoding = getCharEncodingFromString(buffer);
		return encoding;
	}
	return encoding;
}

CharEncoding DetermineCharEncoding::getCharEncodingFromString(std::string & input) {
	CharEncoding encoding = NULL_ENC;
	if ((input == "unicode-1-1-utf-8") || (input == "utf-8") || (input == "utf8")) {
		encoding = UTF_8;
		return encoding;
	} else if (input == "utf-16be") {
		encoding = UTF_16_BE;
		return encoding;
	} else if ((input == "utf-16le") || (input == "utf-16")) {
		encoding = UTF_16_LE;
		return encoding;
	}
	return encoding;
}
} /* namespace Parse */
} /* namespace HTML */
