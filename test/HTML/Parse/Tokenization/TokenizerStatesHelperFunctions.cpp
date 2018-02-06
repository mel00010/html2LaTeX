/*******************************************************************************
 * TokenizerStatesHelperFunctions.cpp
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

#include "TokenizerStatesHelperFunctions.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <stack>
#include <string>

#include <HTML/Parse/Tokenization/TokenizationTypes.hpp>
#include <HTML/Parse/Tokenization/Tokenizer.hpp>


namespace HTML {
namespace Parse {
namespace Tokenization {

using ::testing::_;
using ::testing::InSequence;
using ::testing::Sequence;

::testing::AssertionResult AssertState(__attribute__ ((unused)) const char* state_expr,
									   const char* tokenizer_expr,
									   const State& state,
									   const Tokenizer& tokenizer) {
	if (tokenizer.getCurrentState() == state)
		return ::testing::AssertionSuccess();

	return ::testing::AssertionFailure()
		<< tokenizer_expr << " is not in state " << state << ".  \n"
		<< "Actual state:  " << tokenizer.getCurrentState();
}

} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */


