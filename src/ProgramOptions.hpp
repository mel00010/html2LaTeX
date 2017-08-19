/*******************************************************************************
 * ProgramOptions.hpp
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
#ifndef PROGRAMOPTIONS_HPP_
#define PROGRAMOPTIONS_HPP_

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/positional_options.hpp>
#include <iostream>
#include <string>
#include <vector>

/**
 * @file ProgramOptions.hpp
 * @brief Defines the Options class
 */


/**
 * @brief Helper function to simplify the printing of std::vectors.
 * @param os A reference to the output stream to be written to.
 * @param v A reference to a std::vector of some type T to be written to the output stream.
 * @return A reference to the output stream provided as a parameter.
 */
template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v);

/**
 * @brief Parses program options.
 *
 * Uses boost::program_options to parse the command line arguments passed to the program.
 */
class Options {
	public:

		/**
		 * @brief Helper type for exception handling
		 */
		enum EXIT_TYPE {
			EXIT /**< @brief The function upstream should exit if it catches this exception. */
		};
		public:

		/**
		 * @brief Parses the program options.
		 *
		 * Defines and parses the program options from the command line arguments given using boost::program_options.
		 * @param argc The number of strings in argv.
		 * @param argv The array of null terminated char* strings.
		 * @exception boost::program_options::error Boost encountered an error while parsing the program options.
		 * @exception EXIT_TYPE Indicates to the upstream function that it should exit.
		 * @exception std::exception The function threw an exception.
		 * @exception ... The function caught and rethrew an exception.
		 */
		void parse(int argc, char** argv);

	private:

		/**
		 * @brief Returns the base name of a file.
		 * @param p1 The path to the file.
		 * @return A std::string containing the basename of the file passed in p1.
		 */
		std::string basename(const std::string& p1);

		/**
		 * @brief Splits up an arbitrarily large amount of positional arguments into vectors of strings.
		 *
		 * Workaround for boost::program_options not supporting the construction of usage strings with an arbitrarily large amount of positional arguments
		 * @param p a reference to a boost::positional_options_description object to pull positional options from when generating the strings
		 * @return A std::vector of std::strings created from p.
		 */
		std::vector<std::string> getUnlimitedPositionalArgs(const boost::program_options::positional_options_description& p);

		/**
		 * @brief Creates a usage string.
		 *
		 * Creates a program usage string for display in the help information.
		 * @param programName A reference to a std::string holding the program name
		 * @param desc A reference to a boost::program_options::options_description object defining all of the named arguments.
		 * @param p A reference to a boost::program_options::positional_options_description object defining all of the positional arguments.
		 * @return A std::string containing the assembled usage string.
		 */
		std::string makeUsageString(
				const std::string& programName,
				const boost::program_options::options_description& desc,
				boost::program_options::positional_options_description& p);


	public:
		std::string inputFilename; /**< @brief The path to the input file to be processed */
		std::string outputFilename; /**< @brief The path to the output file */
};

#endif /* PROGRAMOPTIONS_HPP_ */

