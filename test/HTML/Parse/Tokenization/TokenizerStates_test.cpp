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
	TEST_STATE_FUNCTION_1(characterReferenceInDataState, U"\t"s, CHARACTER_REFERENCE_IN_DATA, DATA, CharacterToken('&'));
	TEST_STATE_FUNCTION_1(characterReferenceInDataState, U"Aacute;"s, CHARACTER_REFERENCE_IN_DATA, DATA, CharacterToken(U'\U000000C1'));
	TEST_STATE_FUNCTION_2(characterReferenceInDataState, U"acE;"s, CHARACTER_REFERENCE_IN_DATA, DATA, CharacterToken(U'\U0000223E'), CharacterToken(U'\U00000333'));
}

TEST(HTML_Parse_Tokenization_States, RCDATAState) {
	TEST_STATE_FUNCTION_0(RCDATAState, U"&"s, RCDATA, CHARACTER_REFERENCE_IN_RCDATA);
	TEST_STATE_FUNCTION_0(RCDATAState, U"<"s, RCDATA, RCDATA_LESS_THAN_SIGN);
	TEST_STATE_FUNCTION_PARSE_ERROR_1(RCDATAState, U"\0"s, RCDATA, RCDATA, CharacterToken(U'\U0000FFFD'));
	TEST_STATE_FUNCTION_1(RCDATAState, U""s, RCDATA, RCDATA, EOFToken());
	TEST_STATE_FUNCTION_1(RCDATAState, U"\U12345678"s, RCDATA, RCDATA, CharacterToken(U'\U12345678'));
}

TEST(HTML_Parse_Tokenization_States, characterReferenceInRCDATAState) {
	TEST_STATE_FUNCTION_1(characterReferenceInRCDATAState, U"\t"s, CHARACTER_REFERENCE_IN_RCDATA, RCDATA, CharacterToken('&'));
	TEST_STATE_FUNCTION_1(characterReferenceInRCDATAState, U"Aacute;"s, CHARACTER_REFERENCE_IN_RCDATA, RCDATA, CharacterToken(U'\U000000C1'));
	TEST_STATE_FUNCTION_2(characterReferenceInRCDATAState, U"acE;"s, CHARACTER_REFERENCE_IN_RCDATA, RCDATA, CharacterToken(U'\U0000223E'), CharacterToken(U'\U00000333'));
}

TEST(HTML_Parse_Tokenization_States, RAWTEXTState) {
	TEST_STATE_FUNCTION_0(RAWTEXTState, U"<"s, RAWTEXT, RAWTEXT_LESS_THAN_SIGN);
	TEST_STATE_FUNCTION_PARSE_ERROR_1(RAWTEXTState, U"\0"s, RAWTEXT, RAWTEXT, CharacterToken(U'\U0000FFFD'));
	TEST_STATE_FUNCTION_1(RAWTEXTState, U""s, RAWTEXT, RAWTEXT, EOFToken());
	TEST_STATE_FUNCTION_1(RAWTEXTState, U"\U12345678"s, RAWTEXT, RAWTEXT, CharacterToken(U'\U12345678'));
}

TEST(HTML_Parse_Tokenization_States, scriptDataState) {
	TEST_STATE_FUNCTION_0(scriptDataState, U"<", SCRIPT_DATA, SCRIPT_DATA_LESS_THAN_SIGN);
	TEST_STATE_FUNCTION_PARSE_ERROR_1(scriptDataState, U"\0"s, SCRIPT_DATA, SCRIPT_DATA, CharacterToken(U'\U0000FFFD'));
	TEST_STATE_FUNCTION_1(scriptDataState, U""s, SCRIPT_DATA, SCRIPT_DATA, EOFToken());
	TEST_STATE_FUNCTION_1(scriptDataState, U"\U12345678"s, SCRIPT_DATA, SCRIPT_DATA, CharacterToken(U'\U12345678'));
}

TEST(HTML_Parse_Tokenization_States, plainTextState) {
	TEST_STATE_FUNCTION_PARSE_ERROR_1(plainTextState, U"\0"s, PLAINTEXT, PLAINTEXT, CharacterToken(U'\U0000FFFD'));
	TEST_STATE_FUNCTION_1(plainTextState, U""s, PLAINTEXT, PLAINTEXT, EOFToken());
	TEST_STATE_FUNCTION_1(plainTextState, U"\U12345678"s, PLAINTEXT, PLAINTEXT, CharacterToken(U'\U12345678'));
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
