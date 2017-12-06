/*******************************************************************************
 * TokenizerStates_test.cpp
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

#include "TokenizerStates_test_macros.hpp"

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

class MockTreeConstructor {
	public:
		MOCK_METHOD1(dispatch, void(Tokenization::Token token));
		MOCK_METHOD1(dispatchParseError, void(ParseError error));
};

::testing::AssertionResult AssertState(const char* state_expr,
									   const char* tokenizer_expr,
									   const State& state,
									   const Tokenizer<MockTreeConstructor>& tokenizer) {
	if (tokenizer.getCurrentState() == state)
		return ::testing::AssertionSuccess();

	return ::testing::AssertionFailure()
		<< tokenizer_expr << " is not in state " << state_expr << ".  \n\n"
		<< "Actual state:  " << tokenizer.getCurrentState();
}

TEST(HTML_Parse_Tokenization_States, dataState) {
	TEST_STATE_FUNCTION_0(dataState, U"&"s, DATA, CHARACTER_REFERENCE_IN_DATA);
	TEST_STATE_FUNCTION_0(dataState, U"<"s, DATA, TAG_OPEN);
	TEST_STATE_FUNCTION_PARSE_ERROR_1(dataState, U"\0"s, DATA, DATA, CharacterToken(U'\0'));
	TEST_STATE_FUNCTION_1(dataState, U""s, DATA, DATA, EOFToken());
	TEST_STATE_FUNCTION_1(dataState, U"\U12345678"s, DATA, DATA, CharacterToken(U'\U12345678'));
}

TEST(HTML_Parse_Tokenization_States, characterReferenceInDataState) {

}

TEST(HTML_Parse_Tokenization_States, RCDATAState) {

}

TEST(HTML_Parse_Tokenization_States, characterReferenceINRCDATAState) {

}

TEST(HTML_Parse_Tokenization_States, RAWTEXTState) {

}

TEST(HTML_Parse_Tokenization_States, scriptDataState) {

}

TEST(HTML_Parse_Tokenization_States, plainTextState) {

}

TEST(HTML_Parse_Tokenization_States, tagOpenState) {

}

TEST(HTML_Parse_Tokenization_States, endTagOpenState) {

}

TEST(HTML_Parse_Tokenization_States, tagNameState) {

}

TEST(HTML_Parse_Tokenization_States, RCDATALessThanSignState) {

}

TEST(HTML_Parse_Tokenization_States, RCDATAEndTagOpenState) {

}

TEST(HTML_Parse_Tokenization_States, RCDATAEndTagNameState) {

}

TEST(HTML_Parse_Tokenization_States, RAWTEXTLessThanSignState) {

}

TEST(HTML_Parse_Tokenization_States, RAWTEXTEndTagOpenState) {

}

TEST(HTML_Parse_Tokenization_States, RAWTEXTEndTagNameState) {

}

TEST(HTML_Parse_Tokenization_States, scriptDataLessThanSignState) {

}

TEST(HTML_Parse_Tokenization_States, scriptDataEndTagOpenState) {

}

TEST(HTML_Parse_Tokenization_States, scriptDataEndTagNameState) {

}

TEST(HTML_Parse_Tokenization_States, scriptDataEscapeStartState) {

}

TEST(HTML_Parse_Tokenization_States, scriptDataEscapeStartDashState) {

}

TEST(HTML_Parse_Tokenization_States, scriptDataEscapedState) {

}

TEST(HTML_Parse_Tokenization_States, scriptDataEscapedDashState) {

}

TEST(HTML_Parse_Tokenization_States, scriptDataEscapedDashDashState) {

}

TEST(HTML_Parse_Tokenization_States, scriptDataEscapedLessThanSignState) {

}

TEST(HTML_Parse_Tokenization_States, scriptDataEscapedEndTagOpenState) {

}

TEST(HTML_Parse_Tokenization_States, scriptDataEscapedEndTagNameState) {

}

TEST(HTML_Parse_Tokenization_States, scriptDataDoubleEscapeStartState) {

}

TEST(HTML_Parse_Tokenization_States, scriptDataDoubleEscapedState) {

}

TEST(HTML_Parse_Tokenization_States, scriptDataDoubleEscapedDashState) {

}

TEST(HTML_Parse_Tokenization_States, scriptDataDoubleEscapedDashDashState) {

}

TEST(HTML_Parse_Tokenization_States, scriptDataDoubleEscapedLessThanSignState) {

}

TEST(HTML_Parse_Tokenization_States, scriptDataDoubleEscapeEndState) {

}

TEST(HTML_Parse_Tokenization_States, beforeAttributeNameState) {

}

TEST(HTML_Parse_Tokenization_States, attributeNameState) {

}

TEST(HTML_Parse_Tokenization_States, beforeAttributeValueState) {

}

TEST(HTML_Parse_Tokenization_States, afterAttributeNameState) {

}

TEST(HTML_Parse_Tokenization_States, attributeValueDoubleQuotedState) {

}

TEST(HTML_Parse_Tokenization_States, attributeValueSingleQuotedState) {

}

TEST(HTML_Parse_Tokenization_States, attributeValueUnquotedState) {

}

TEST(HTML_Parse_Tokenization_States, characterReferenceInAttributeValueState) {

}

TEST(HTML_Parse_Tokenization_States, afterAttributeQuotedState) {

}

TEST(HTML_Parse_Tokenization_States, selfClosingStartTagState) {

}

TEST(HTML_Parse_Tokenization_States, bogusCommentState) {

}

TEST(HTML_Parse_Tokenization_States, markupDeclarationOpenState) {

}

TEST(HTML_Parse_Tokenization_States, commentStartState) {

}

TEST(HTML_Parse_Tokenization_States, commentStartDashState) {

}

TEST(HTML_Parse_Tokenization_States, commentState) {

}

TEST(HTML_Parse_Tokenization_States, commentEndDashState) {

}

TEST(HTML_Parse_Tokenization_States, commentEndState) {

}

TEST(HTML_Parse_Tokenization_States, commentEndBangState) {

}

TEST(HTML_Parse_Tokenization_States, DOCTYPEState) {

}

TEST(HTML_Parse_Tokenization_States, beforeDOCTYPENameState) {

}

TEST(HTML_Parse_Tokenization_States, DOCTYPENameState) {

}

TEST(HTML_Parse_Tokenization_States, afterDOCTYPENameState) {

}

TEST(HTML_Parse_Tokenization_States, afterDOCTYPEPublicKeywordState) {

}

TEST(HTML_Parse_Tokenization_States, beforeDOCTYPEPublicIdentifierState) {

}

TEST(HTML_Parse_Tokenization_States, DOCTYPEPublicIdentifierDoubleQuotedState) {

}

TEST(HTML_Parse_Tokenization_States, DOCTYPEPublicIdentifierSingleQuotedState) {

}

TEST(HTML_Parse_Tokenization_States, afterDOCTYPEPublicIdentifierState) {

}

TEST(HTML_Parse_Tokenization_States, betweenDOCTYPEPublicAndSystemIdentifiersState) {

}

TEST(HTML_Parse_Tokenization_States, afterDOCTYPESystemKeywordState) {

}

TEST(HTML_Parse_Tokenization_States, beforeDOCTYPESystemIdentifierState) {

}

TEST(HTML_Parse_Tokenization_States, DOCTYPESystemIdentifierDoubleQuotedState) {

}

TEST(HTML_Parse_Tokenization_States, DOCTYPESystemIdentifierSingleQuotedState) {

}

TEST(HTML_Parse_Tokenization_States, afterDOCTYPESystemIdentifierState) {

}

TEST(HTML_Parse_Tokenization_States, bogusDOCTYPEState) {

}

TEST(HTML_Parse_Tokenization_States, CDATASectionState) {

}

} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */
