/*******************************************************************************
 * TokenizerStates_test_macros.hpp
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
#ifndef TEST_HTML_PARSE_TOKENIZATION_TOKENIZERSTATES_TEST_MACROS_HPP_
#define TEST_HTML_PARSE_TOKENIZATION_TOKENIZERSTATES_TEST_MACROS_HPP_

#define EXPECT_STATE(state) \
	EXPECT_PRED_FORMAT2(AssertState, state, tokenizer);
#define EXPECT_TOKEN(token) \
	EXPECT_CALL(mock_tree_constructor, dispatch(Token(token))).InSequence(sequence);
#define EXPECT_PARSE_ERROR(parse_error) \
	EXPECT_CALL(mock_tree_constructor, dispatchParseError(parse_error));

#define TEST_STATE_0(test_string, start_state, end_state) \
	{ \
		MockTreeConstructor mock_tree_constructor; \
		Tokenizer tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		std::invoke(Tokenizer::getStateFunction(start_state), tokenizer); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_1(test_string, start_state, end_state, _1) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_TOKEN(_1); \
		Tokenizer tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		std::invoke(Tokenizer::getStateFunction(start_state), tokenizer); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_2(test_string, start_state, end_state, _1, _2) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_TOKEN(_1); \
		EXPECT_TOKEN(_2); \
		Tokenizer tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		std::invoke(Tokenizer::getStateFunction(start_state), tokenizer); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_3(test_string, start_state, end_state, _1, _2, _3) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_TOKEN(_1); \
		EXPECT_TOKEN(_2); \
		EXPECT_TOKEN(_3); \
		Tokenizer tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		std::invoke(Tokenizer::getStateFunction(start_state), tokenizer); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_4(test_string, start_state, end_state, _1, _2, _3, _4) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_TOKEN(_1); \
		EXPECT_TOKEN(_2); \
		EXPECT_TOKEN(_3); \
		EXPECT_TOKEN(_4); \
		Tokenizer tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		std::invoke(Tokenizer::getStateFunction(start_state), tokenizer); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_5(test_string, start_state, end_state, _1, _2, _3, _4, _5) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_TOKEN(_1); \
		EXPECT_TOKEN(_2); \
		EXPECT_TOKEN(_3); \
		EXPECT_TOKEN(_4); \
		EXPECT_TOKEN(_5); \
		Tokenizer tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		std::invoke(Tokenizer::getStateFunction(start_state), tokenizer); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_6(test_string, start_state, end_state, _1, _2, _3, _4, _5, _6) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_TOKEN(_1); \
		EXPECT_TOKEN(_2); \
		EXPECT_TOKEN(_3); \
		EXPECT_TOKEN(_4); \
		EXPECT_TOKEN(_5); \
		EXPECT_TOKEN(_6); \
		Tokenizer tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		std::invoke(Tokenizer::getStateFunction(start_state), tokenizer); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_7(test_string, start_state, end_state, _1, _2, _3, _4, _5, _6, _7) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_TOKEN(_1); \
		EXPECT_TOKEN(_2); \
		EXPECT_TOKEN(_3); \
		EXPECT_TOKEN(_4); \
		EXPECT_TOKEN(_5); \
		EXPECT_TOKEN(_6); \
		EXPECT_TOKEN(_7); \
		Tokenizer tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		std::invoke(Tokenizer::getStateFunction(start_state), tokenizer); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_8(test_string, start_state, end_state, _1, _2, _3, _4, _5, _6, _7, _8) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_TOKEN(_1); \
		EXPECT_TOKEN(_2); \
		EXPECT_TOKEN(_3); \
		EXPECT_TOKEN(_4); \
		EXPECT_TOKEN(_5); \
		EXPECT_TOKEN(_6); \
		EXPECT_TOKEN(_7); \
		EXPECT_TOKEN(_8); \
		Tokenizer tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		std::invoke(Tokenizer::getStateFunction(start_state), tokenizer); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_9(test_string, start_state, end_state, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_TOKEN(_1); \
		EXPECT_TOKEN(_2); \
		EXPECT_TOKEN(_3); \
		EXPECT_TOKEN(_4); \
		EXPECT_TOKEN(_5); \
		EXPECT_TOKEN(_6); \
		EXPECT_TOKEN(_7); \
		EXPECT_TOKEN(_8); \
		EXPECT_TOKEN(_9); \
		Tokenizer tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		std::invoke(Tokenizer::getStateFunction(start_state), tokenizer); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_10(test_string, start_state, end_state, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_TOKEN(_1); \
		EXPECT_TOKEN(_2); \
		EXPECT_TOKEN(_3); \
		EXPECT_TOKEN(_4); \
		EXPECT_TOKEN(_5); \
		EXPECT_TOKEN(_6); \
		EXPECT_TOKEN(_7); \
		EXPECT_TOKEN(_8); \
		EXPECT_TOKEN(_9); \
		EXPECT_TOKEN(_10); \
		Tokenizer tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		std::invoke(Tokenizer::getStateFunction(start_state), tokenizer); \
		EXPECT_STATE(end_state); \
	}

#define TEST_STATE_PE_0(test_string, start_state, end_state) \
	{ \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_PARSE_ERROR(ParseError::OTHER); \
		Tokenizer tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		std::invoke(Tokenizer::getStateFunction(start_state), tokenizer); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_PE_1(test_string, start_state, end_state, _1) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_PARSE_ERROR(ParseError::OTHER); \
		EXPECT_TOKEN(_1); \
		Tokenizer tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		std::invoke(Tokenizer::getStateFunction(start_state), tokenizer); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_PE_2(test_string, start_state, end_state, _1, _2) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_PARSE_ERROR(ParseError::OTHER); \
		EXPECT_TOKEN(_1); \
		EXPECT_TOKEN(_2); \
		Tokenizer tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		std::invoke(Tokenizer::getStateFunction(start_state), tokenizer); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_PE_3(test_string, start_state, end_state, _1, _2, _3) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_PARSE_ERROR(ParseError::OTHER); \
		EXPECT_TOKEN(_1); \
		EXPECT_TOKEN(_2); \
		EXPECT_TOKEN(_3); \
		Tokenizer tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		std::invoke(Tokenizer::getStateFunction(start_state), tokenizer); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_PE_4(test_string, start_state, end_state, _1, _2, _3, _4) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_PARSE_ERROR(ParseError::OTHER); \
		EXPECT_TOKEN(_1); \
		EXPECT_TOKEN(_2); \
		EXPECT_TOKEN(_3); \
		EXPECT_TOKEN(_4); \
		Tokenizer tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		std::invoke(Tokenizer::getStateFunction(start_state), tokenizer); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_PE_5(test_string, start_state, end_state, _1, _2, _3, _4, _5) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_PARSE_ERROR(ParseError::OTHER); \
		EXPECT_TOKEN(_1); \
		EXPECT_TOKEN(_2); \
		EXPECT_TOKEN(_3); \
		EXPECT_TOKEN(_4); \
		EXPECT_TOKEN(_5); \
		Tokenizer tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		std::invoke(Tokenizer::getStateFunction(start_state), tokenizer); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_PE_6(test_string, start_state, end_state, _1, _2, _3, _4, _5, _6) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_PARSE_ERROR(ParseError::OTHER); \
		EXPECT_TOKEN(_1); \
		EXPECT_TOKEN(_2); \
		EXPECT_TOKEN(_3); \
		EXPECT_TOKEN(_4); \
		EXPECT_TOKEN(_5); \
		EXPECT_TOKEN(_6); \
		Tokenizer tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		std::invoke(Tokenizer::getStateFunction(start_state), tokenizer); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_PE_7(test_string, start_state, end_state, _1, _2, _3, _4, _5, _6, _7) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_PARSE_ERROR(ParseError::OTHER); \
		EXPECT_TOKEN(_1); \
		EXPECT_TOKEN(_2); \
		EXPECT_TOKEN(_3); \
		EXPECT_TOKEN(_4); \
		EXPECT_TOKEN(_5); \
		EXPECT_TOKEN(_6); \
		EXPECT_TOKEN(_7); \
		Tokenizer tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		std::invoke(Tokenizer::getStateFunction(start_state), tokenizer); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_PE_8(test_string, start_state, end_state, _1, _2, _3, _4, _5, _6, _7, _8) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_PARSE_ERROR(ParseError::OTHER); \
		EXPECT_TOKEN(_1); \
		EXPECT_TOKEN(_2); \
		EXPECT_TOKEN(_3); \
		EXPECT_TOKEN(_4); \
		EXPECT_TOKEN(_5); \
		EXPECT_TOKEN(_6); \
		EXPECT_TOKEN(_7); \
		EXPECT_TOKEN(_8); \
		Tokenizer tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		std::invoke(Tokenizer::getStateFunction(start_state), tokenizer); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_PE_9(test_string, start_state, end_state, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_PARSE_ERROR(ParseError::OTHER); \
		EXPECT_TOKEN(_1); \
		EXPECT_TOKEN(_2); \
		EXPECT_TOKEN(_3); \
		EXPECT_TOKEN(_4); \
		EXPECT_TOKEN(_5); \
		EXPECT_TOKEN(_6); \
		EXPECT_TOKEN(_7); \
		EXPECT_TOKEN(_8); \
		EXPECT_TOKEN(_9); \
		Tokenizer tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		std::invoke(Tokenizer::getStateFunction(start_state), tokenizer); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_PE_10(test_string, start_state, end_state, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_PARSE_ERROR(ParseError::OTHER); \
		EXPECT_TOKEN(_1); \
		EXPECT_TOKEN(_2); \
		EXPECT_TOKEN(_3); \
		EXPECT_TOKEN(_4); \
		EXPECT_TOKEN(_5); \
		EXPECT_TOKEN(_6); \
		EXPECT_TOKEN(_7); \
		EXPECT_TOKEN(_8); \
		EXPECT_TOKEN(_9); \
		EXPECT_TOKEN(_10); \
		Tokenizer tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		std::invoke(Tokenizer::getStateFunction(start_state), tokenizer); \
		EXPECT_STATE(end_state); \
	}




#endif /* TEST_HTML_PARSE_TOKENIZATION_TOKENIZERSTATES_TEST_MACROS_HPP_ */
