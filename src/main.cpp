/*******************************************************************************
 * main.cpp
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

#include <fstream>
#include <iostream>

#include "HTML/HTMLTypes.hpp"
#include "HTML/Parse/DetermineCharEncoding.hpp"
//#include "ProgramOptions.hpp"

/**
 * @file src/main.cpp
 * @brief The main file of html2LaTeX
 */
/**
 * @dir src
 * @brief Holds all of the source files and headers in html2LaTeX, excluding tests.
 */

/**
 * @brief The main function of html2LaTeX
 * @param argc
 * @param argv
 * @return Returns 0 if there are no errors.
 */
int main(int argc, char** argv) {
  //	Options options;
  //	try {
  //		options.parse(argc, argv);
  //	}
  //	catch (...) {
  //		return 1;
  //	}

  std::ifstream file;
  //  try {
  //    file.open(options.inputFilename, std::istream::binary);
  //  } catch (...) {
  //    return 1;
  //  }
  HTML::Parse::DetermineCharEncoding determineCharEncoding;
  HTML::ContentType contentType;
  try {
    contentType = determineCharEncoding.determineCharEncoding(file);
  } catch (...) {
    return 1;
  }
  std::cout << contentType << std::endl;
  return 0;
}
