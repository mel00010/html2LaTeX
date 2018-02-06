/*******************************************************************************
 * TokenizerStatesHelperFunctions.hpp
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
#ifndef TEST_HTML_PARSE_TOKENIZATION_TOKENIZERSTATESHELPERFUNCTIONS_HPP_
#define TEST_HTML_PARSE_TOKENIZATION_TOKENIZERSTATESHELPERFUNCTIONS_HPP_

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

using namespace std::literals;

class MockTreeConstructor : public TreeConstruction::TreeConstructorInterface {
	public:
		MOCK_METHOD1(dispatch, void(const Tokenization::Token& token));
		MOCK_METHOD1(dispatchParseError, void(const ParseError& error));
};

::testing::AssertionResult AssertState(const char* state_expr,
									   const char* tokenizer_expr,
									   const State& state,
									   const Tokenizer& tokenizer);
class StateTester {
	public:
		StateTester(const State& start_state) : start_state(start_state) {}
	public:
		void register_expected_call(__attribute__ ((unused)) MockTreeConstructor& mock_tree_constructor,
									__attribute__ ((unused)) Sequence& sequence) {
		}
		template<typename T>
		void register_expected_call(MockTreeConstructor& mock_tree_constructor, Sequence& sequence,
									T t) {
			EXPECT_CALL(mock_tree_constructor, dispatch(Token(t))).InSequence(sequence);
		}
		template<typename T, typename... Args>
		void register_expected_call(MockTreeConstructor& mock_tree_constructor, Sequence& sequence,
									T first, Args... args) {
			EXPECT_CALL(mock_tree_constructor, dispatch(Token(first))).InSequence(sequence);
			register_expected_call(mock_tree_constructor, sequence, args...);
		}
		void test(const State& end_state, const std::u32string& string) {
			MockTreeConstructor mock_tree_constructor;
			Tokenizer tokenizer(string, 0, start_state, mock_tree_constructor);

			Tokenizer::StateFunction state_function = Tokenizer::getStateFunction(start_state);
			(tokenizer.*state_function)();

			EXPECT_PRED_FORMAT2(AssertState, end_state, tokenizer);

		}

		template<bool, typename... Args>
		void test(const State& end_state, const std::u32string& string, bool first, Args... args) {
			Sequence sequence;
			MockTreeConstructor mock_tree_constructor;
			if(first) {
				EXPECT_CALL(mock_tree_constructor, dispatchParseError(ParseError::OTHER));
			}
			register_expected_call(mock_tree_constructor, sequence, args...);

			Tokenizer tokenizer(string, 0, start_state, mock_tree_constructor);

			Tokenizer::StateFunction state_function = Tokenizer::getStateFunction(start_state);
			(tokenizer.*state_function)();

			EXPECT_PRED_FORMAT2(AssertState, end_state, tokenizer);
		}

		template<typename T, typename... Args>
		void test(const State& end_state, const std::u32string& string, T first, Args... args) {
			Sequence sequence;
			MockTreeConstructor mock_tree_constructor;

			register_expected_call(mock_tree_constructor, sequence, first, args...);

			Tokenizer tokenizer(string, 0, start_state, mock_tree_constructor);

			Tokenizer::StateFunction state_function = Tokenizer::getStateFunction(start_state);
			(tokenizer.*state_function)();

			EXPECT_PRED_FORMAT2(AssertState, end_state, tokenizer);
		}
	private:
		const State& start_state;
};

} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */



#endif /* TEST_HTML_PARSE_TOKENIZATION_TOKENIZERSTATESHELPERFUNCTIONS_HPP_ */
