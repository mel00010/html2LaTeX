/*******************************************************************************
 * ProgramOptions.cpp
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

#include "ProgramOptions.hpp"

#include <boost/program_options.hpp>

#include <stddef.h>
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <sstream>
#include <stdexcept>

/**
 * @file ProgramOptions.cpp
 * @brief Implements ProgramOptions.hpp
 */

template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
	std::copy(v.begin(), v.end(), std::ostream_iterator<T>(os, " "));
	return os;
}

void Options::parse(int argc, char** argv) {
	boost::program_options::options_description desc("General Options");
	boost::program_options::options_description hidden;
	boost::program_options::options_description allOptions;
	boost::program_options::positional_options_description p;

	try {
		std::vector<std::string> configFileNames;
		desc.add_options()
		("help,h", "Display help message")
		("version,v", "Display version number")
		("config", boost::program_options::value(&configFileNames), "Config file where options may be specified (can be specified more than once)");

		hidden.add_options()
		("input", boost::program_options::value<std::string>(&inputFilename)->required(), "Input file")
		("output", boost::program_options::value<std::string>(&outputFilename)->required(), "Output file");

		allOptions.add(desc);
		allOptions.add(hidden);

		p.add("input", 1);
		p.add("output", 1);

		boost::program_options::variables_map vm;
		boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(allOptions).positional(p).run(), vm);

		if (vm.count("help")) {
			std::cout << makeUsageString(basename(argv[0]), desc, p) << '\n';
			throw EXIT_TYPE::EXIT;
		}

		if (vm.count("config") > 0) {
			configFileNames = vm["config"].as<std::vector<std::string> >();

			for (size_t i = 0; i < configFileNames.size(); ++i) {
				std::ifstream ifs(configFileNames[i].c_str());

				if (ifs.fail()) {
					throw std::runtime_error(std::string("Error opening config file: ") + configFileNames[i]);
				}

				boost::program_options::store(boost::program_options::parse_config_file(ifs, allOptions), vm);
			}
		}
		boost::program_options::notify(vm);
	}
	catch (boost::program_options::error& e) {
		std::cerr << "Error: " << e.what() << "\n";
		std::cerr << makeUsageString(basename(argv[0]), desc, p) << '\n';
		throw;
	}
	catch (EXIT_TYPE&) {
		throw;
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << "\n";
		throw;
	}
	catch (...) {
		std::cerr << "Exception of unknown type!\n";
		throw;
	}
}
std::string Options::basename(const std::string& p) {
#ifdef HAVE_BOOST_FILESYSTEM
	return boost::filesystem::path(p).stem().string();
#else
	size_t start = p.find_last_of("/");
	if (start == std::string::npos) {
		start = 0;
	}
	else
		++start;
	return p.substr(start);
#endif
}

// Boost doesn't offer any obvious way to construct a usage string
// from an infinite list of positional parameters.  This hack
// should work in most reasonable cases.

std::vector<std::string> Options::getUnlimitedPositionalArgs(const boost::program_options::positional_options_description& p) {
	assert(p.max_total_count() == std::numeric_limits<unsigned>::max());

	std::vector<std::string> parts;

	// reasonable upper limit for number of positional options:
	const int MAX = 1000;
	std::string last = p.name_for_position(MAX);

	for (size_t i = 0; true; ++i) {
		std::string cur = p.name_for_position(i);
		if (cur == last) {
			parts.push_back(cur);
			parts.push_back('[' + cur + ']');
			parts.push_back("...");
			return parts;
		}
		parts.push_back(cur);
	}
	return parts; // never get here
}

std::string Options::makeUsageString(const std::string& program_name, const boost::program_options::options_description& desc,
		boost::program_options::positional_options_description& p) {
	std::vector<std::string> parts;
	parts.push_back("Usage: ");
	parts.push_back(program_name);
	size_t N = p.max_total_count();
	if (N == std::numeric_limits<unsigned>::max()) {
		std::vector<std::string> args = getUnlimitedPositionalArgs(p);
		parts.insert(parts.end(), args.begin(), args.end());
	} else {
		for (size_t i = 0; i < N; ++i) {
			parts.push_back(p.name_for_position(i));
		}
	}
	if (desc.options().size() > 0) {
		parts.push_back("[options]");
	}
	std::ostringstream oss;
	std::copy(parts.begin(), parts.end(), std::ostream_iterator<std::string>(oss, " "));
	oss << '\n' << desc;
	return oss.str();
}
