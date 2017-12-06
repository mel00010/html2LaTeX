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

#define TEST_STATE_FUNCTION_0(state_function, test_string, start_state, end_state) \
	{ \
		MockTreeConstructor mock_tree_constructor; \
		Tokenizer<MockTreeConstructor> tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		tokenizer.state_function(); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_FUNCTION_1(state_function, test_string, start_state, end_state, _1) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_TOKEN(_1); \
		Tokenizer<MockTreeConstructor> tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		tokenizer.state_function(); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_FUNCTION_2(state_function, test_string, start_state, end_state, _1, _2) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_TOKEN(_1); \
		EXPECT_TOKEN(_2); \
		Tokenizer<MockTreeConstructor> tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		tokenizer.state_function(); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_FUNCTION_3(state_function, test_string, start_state, end_state, _1, _2, _3) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_TOKEN(_1); \
		EXPECT_TOKEN(_2); \
		EXPECT_TOKEN(_3); \
		Tokenizer<MockTreeConstructor> tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		tokenizer.state_function(); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_FUNCTION_4(state_function, test_string, start_state, end_state, _1, _2, _3, _4) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_TOKEN(_1); \
		EXPECT_TOKEN(_2); \
		EXPECT_TOKEN(_3); \
		EXPECT_TOKEN(_4); \
		Tokenizer<MockTreeConstructor> tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		tokenizer.state_function(); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_FUNCTION_5(state_function, test_string, start_state, end_state, _1, _2, _3, _4, _5) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_TOKEN(_1); \
		EXPECT_TOKEN(_2); \
		EXPECT_TOKEN(_3); \
		EXPECT_TOKEN(_4); \
		EXPECT_TOKEN(_5); \
		Tokenizer<MockTreeConstructor> tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		tokenizer.state_function(); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_FUNCTION_6(state_function, test_string, start_state, end_state, _1, _2, _3, _4, _5, _6) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_TOKEN(_1); \
		EXPECT_TOKEN(_2); \
		EXPECT_TOKEN(_3); \
		EXPECT_TOKEN(_4); \
		EXPECT_TOKEN(_5); \
		EXPECT_TOKEN(_6); \
		Tokenizer<MockTreeConstructor> tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		tokenizer.state_function(); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_FUNCTION_7(state_function, test_string, start_state, end_state, _1, _2, _3, _4, _5, _6, _7) \
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
		Tokenizer<MockTreeConstructor> tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		tokenizer.state_function(); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_FUNCTION_8(state_function, test_string, start_state, end_state, _1, _2, _3, _4, _5, _6, _7, _8) \
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
		Tokenizer<MockTreeConstructor> tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		tokenizer.state_function(); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_FUNCTION_9(state_function, test_string, start_state, end_state, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
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
		Tokenizer<MockTreeConstructor> tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		tokenizer.state_function(); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_FUNCTION_10(state_function, test_string, start_state, end_state, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
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
		Tokenizer<MockTreeConstructor> tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		tokenizer.state_function(); \
		EXPECT_STATE(end_state); \
	}

#define TEST_STATE_FUNCTION_PARSE_ERROR_0(state_function, test_string, start_state, end_state) \
	{ \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_PARSE_ERROR(ParseError::OTHER); \
		Tokenizer<MockTreeConstructor> tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		tokenizer.state_function(); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_FUNCTION_PARSE_ERROR_1(state_function, test_string, start_state, end_state, _1) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_PARSE_ERROR(ParseError::OTHER); \
		EXPECT_TOKEN(_1); \
		Tokenizer<MockTreeConstructor> tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		tokenizer.state_function(); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_FUNCTION_PARSE_ERROR_2(state_function, test_string, start_state, end_state, _1, _2) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_PARSE_ERROR(ParseError::OTHER); \
		EXPECT_TOKEN(_1); \
		EXPECT_TOKEN(_2); \
		Tokenizer<MockTreeConstructor> tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		tokenizer.state_function(); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_FUNCTION_PARSE_ERROR_3(state_function, test_string, start_state, end_state, _1, _2, _3) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_PARSE_ERROR(ParseError::OTHER); \
		EXPECT_TOKEN(_1); \
		EXPECT_TOKEN(_2); \
		EXPECT_TOKEN(_3); \
		Tokenizer<MockTreeConstructor> tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		tokenizer.state_function(); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_FUNCTION_PARSE_ERROR_4(state_function, test_string, start_state, end_state, _1, _2, _3, _4) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_PARSE_ERROR(ParseError::OTHER); \
		EXPECT_TOKEN(_1); \
		EXPECT_TOKEN(_2); \
		EXPECT_TOKEN(_3); \
		EXPECT_TOKEN(_4); \
		Tokenizer<MockTreeConstructor> tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		tokenizer.state_function(); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_FUNCTION_PARSE_ERROR_5(state_function, test_string, start_state, end_state, _1, _2, _3, _4, _5) \
	{ \
		Sequence sequence; \
		MockTreeConstructor mock_tree_constructor; \
		EXPECT_PARSE_ERROR(ParseError::OTHER); \
		EXPECT_TOKEN(_1); \
		EXPECT_TOKEN(_2); \
		EXPECT_TOKEN(_3); \
		EXPECT_TOKEN(_4); \
		EXPECT_TOKEN(_5); \
		Tokenizer<MockTreeConstructor> tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		tokenizer.state_function(); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_FUNCTION_PARSE_ERROR_6(state_function, test_string, start_state, end_state, _1, _2, _3, _4, _5, _6) \
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
		Tokenizer<MockTreeConstructor> tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		tokenizer.state_function(); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_FUNCTION_PARSE_ERROR_7(state_function, test_string, start_state, end_state, _1, _2, _3, _4, _5, _6, _7) \
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
		Tokenizer<MockTreeConstructor> tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		tokenizer.state_function(); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_FUNCTION_PARSE_ERROR_8(state_function, test_string, start_state, end_state, _1, _2, _3, _4, _5, _6, _7, _8) \
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
		Tokenizer<MockTreeConstructor> tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		tokenizer.state_function(); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_FUNCTION_PARSE_ERROR_9(state_function, test_string, start_state, end_state, _1, _2, _3, _4, _5, _6, _7, _8, _9) \
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
		Tokenizer<MockTreeConstructor> tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		tokenizer.state_function(); \
		EXPECT_STATE(end_state); \
	}
#define TEST_STATE_FUNCTION_PARSE_ERROR_10(state_function, test_string, start_state, end_state, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10) \
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
		Tokenizer<MockTreeConstructor> tokenizer(test_string, 0, start_state, mock_tree_constructor); \
		tokenizer.state_function(); \
		EXPECT_STATE(end_state); \
	}




#endif /* TEST_HTML_PARSE_TOKENIZATION_TOKENIZERSTATES_TEST_MACROS_HPP_ */
