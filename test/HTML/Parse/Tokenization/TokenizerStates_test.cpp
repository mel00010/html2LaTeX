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

#include <functional>
#include <list>
#include <stack>
#include <string>

#include <HTML/Parse/Tokenization/TokenizationTypes.hpp>
#include <HTML/Parse/Tokenization/Tokenizer.hpp>
#include <HTML/Parse/TreeConstruction/TreeConstructorInterface.hpp>


namespace HTML {
namespace Parse {
namespace Tokenization {

using ::testing::_;
using ::testing::Const;
using ::testing::InSequence;
using ::testing::Ref;
using ::testing::Sequence;

using namespace std::literals;

class FakeTreeConstructor : public TreeConstruction::TreeConstructorInterface {
	public:
		virtual void dispatch(const Tokenization::Token& token) {

		}
		virtual void dispatchParseError(const ParseError& error) {

		}
		bool parse_error = false;
		std::list<Token> tokens;
};

class MockTreeConstructor : public TreeConstruction::TreeConstructorInterface {
	public:
		MOCK_METHOD1(dispatch, void(const Tokenization::Token& token));
		MOCK_METHOD1(dispatchParseError, void(const ParseError& error));
};

::testing::AssertionResult AssertState(__attribute__ ((unused)) const char* state_expr,
									   const char* tokenizer_expr,
									   const State& state,
									   const Tokenizer& tokenizer) {
	if (tokenizer.getCurrentState() == state)
		return ::testing::AssertionSuccess();

	return ::testing::AssertionFailure()
		<< tokenizer_expr << " is not in state " << state << ".  \n\n"
		<< "Actual state:  " << tokenizer.getCurrentState();
}
::testing::AssertionResult AssertParseError(__attribute__ ((unused)) const char* state_expr,
									   const char* tokenizer_expr,
									   const State& state,
									   const Tokenizer& tokenizer) {
	if (tokenizer.getCurrentState() == state)
		return ::testing::AssertionSuccess();

	return ::testing::AssertionFailure()
		<< tokenizer_expr << " is not in state " << state << ".  \n\n"
		<< "Actual state:  " << tokenizer.getCurrentState();
}


// Section 8.2.4.1
TEST(HTML_Parse_Tokenization_States, dataState) {
	TEST_STATE_0(U"&"s, DATA, CHARACTER_REFERENCE_IN_DATA);
	TEST_STATE_0(U"<"s, DATA, TAG_OPEN);
	TEST_STATE_PE_1(U"\0"s, DATA, DATA, CharacterToken(U'\0'));
	TEST_STATE_1(U""s, DATA, DATA, EOFToken());
	TEST_STATE_1(U"\U12345678"s, DATA, DATA, CharacterToken(U'\U12345678'));
}

// Section 8.2.4.2
TEST(HTML_Parse_Tokenization_States, characterReferenceInDataState) {
	TEST_STATE_1(U"\t"s, CHARACTER_REFERENCE_IN_DATA, DATA, CharacterToken('&'));
	TEST_STATE_1(U"Aacute;"s, CHARACTER_REFERENCE_IN_DATA, DATA, CharacterToken(U'\U000000C1'));
	TEST_STATE_2(U"acE;"s, CHARACTER_REFERENCE_IN_DATA, DATA, CharacterToken(U'\U0000223E'), CharacterToken(U'\U00000333'));
}

// Section 8.2.4.3
TEST(HTML_Parse_Tokenization_States, RCDATAState) {
	TEST_STATE_0(U"&"s, RCDATA, CHARACTER_REFERENCE_IN_RCDATA);
	TEST_STATE_0(U"<"s, RCDATA, RCDATA_LESS_THAN_SIGN);
	TEST_STATE_PE_1(U"\0"s, RCDATA, RCDATA, CharacterToken(U'\U0000FFFD'));
	TEST_STATE_1(U""s, RCDATA, RCDATA, EOFToken());
	TEST_STATE_1(U"\U12345678"s, RCDATA, RCDATA, CharacterToken(U'\U12345678'));
}

// Section 8.2.4.4
TEST(HTML_Parse_Tokenization_States, characterReferenceInRCDATAState) {
	TEST_STATE_1(U"\t"s, CHARACTER_REFERENCE_IN_RCDATA, RCDATA, CharacterToken('&'));
	TEST_STATE_1(U"Aacute;"s, CHARACTER_REFERENCE_IN_RCDATA, RCDATA, CharacterToken(U'\U000000C1'));
	TEST_STATE_2(U"acE;"s, CHARACTER_REFERENCE_IN_RCDATA, RCDATA, CharacterToken(U'\U0000223E'), CharacterToken(U'\U00000333'));
}

// Section 8.2.4.5
TEST(HTML_Parse_Tokenization_States, RAWTEXTState) {
	TEST_STATE_0(U"<"s, RAWTEXT, RAWTEXT_LESS_THAN_SIGN);
	TEST_STATE_PE_1(U"\0"s, RAWTEXT, RAWTEXT, CharacterToken(U'\U0000FFFD'));
	TEST_STATE_1(U""s, RAWTEXT, RAWTEXT, EOFToken());
	TEST_STATE_1(U"\U12345678"s, RAWTEXT, RAWTEXT, CharacterToken(U'\U12345678'));
}

// Section 8.2.4.6
TEST(HTML_Parse_Tokenization_States, scriptDataState) {
	TEST_STATE_0(U"<", SCRIPT_DATA, SCRIPT_DATA_LESS_THAN_SIGN);
	TEST_STATE_PE_1(U"\0"s, SCRIPT_DATA, SCRIPT_DATA, CharacterToken(U'\U0000FFFD'));
	TEST_STATE_1(U""s, SCRIPT_DATA, SCRIPT_DATA, EOFToken());
	TEST_STATE_1(U"\U12345678"s, SCRIPT_DATA, SCRIPT_DATA, CharacterToken(U'\U12345678'));
}

// Section 8.2.4.7
TEST(HTML_Parse_Tokenization_States, plainTextState) {
	TEST_STATE_PE_1(U"\0"s, PLAINTEXT, PLAINTEXT, CharacterToken(U'\U0000FFFD'));
	TEST_STATE_1(U""s, PLAINTEXT, PLAINTEXT, EOFToken());
	TEST_STATE_1(U"\U12345678"s, PLAINTEXT, PLAINTEXT, CharacterToken(U'\U12345678'));
}

// Section 8.2.4.8
TEST(HTML_Parse_Tokenization_States, tagOpenState) {

}

// Section 8.2.4.9
TEST(HTML_Parse_Tokenization_States, endTagOpenState) {

}

// Section 8.2.4.10
TEST(HTML_Parse_Tokenization_States, tagNameState) {

}

// Section 8.2.4.11
TEST(HTML_Parse_Tokenization_States, RCDATALessThanSignState) {

}

// Section 8.2.4.12
TEST(HTML_Parse_Tokenization_States, RCDATAEndTagOpenState) {

}

// Section 8.2.4.13
TEST(HTML_Parse_Tokenization_States, RCDATAEndTagNameState) {

}

// Section 8.2.4.14
TEST(HTML_Parse_Tokenization_States, RAWTEXTLessThanSignState) {

}

// Section 8.2.4.15
TEST(HTML_Parse_Tokenization_States, RAWTEXTEndTagOpenState) {

}

// Section 8.2.4.16
TEST(HTML_Parse_Tokenization_States, RAWTEXTEndTagNameState) {

}

// Section 8.2.4.17
TEST(HTML_Parse_Tokenization_States, scriptDataLessThanSignState) {

}

// Section 8.2.4.18
TEST(HTML_Parse_Tokenization_States, scriptDataEndTagOpenState) {

}

// Section 8.2.4.19
TEST(HTML_Parse_Tokenization_States, scriptDataEndTagNameState) {

}

// Section 8.2.4.20
TEST(HTML_Parse_Tokenization_States, scriptDataEscapeStartState) {

}

// Section 8.2.4.21
TEST(HTML_Parse_Tokenization_States, scriptDataEscapeStartDashState) {

}

// Section 8.2.4.22
TEST(HTML_Parse_Tokenization_States, scriptDataEscapedState) {

}

// Section 8.2.4.23
TEST(HTML_Parse_Tokenization_States, scriptDataEscapedDashState) {

}

// Section 8.2.4.24
TEST(HTML_Parse_Tokenization_States, scriptDataEscapedDashDashState) {

}

// Section 8.2.4.25
TEST(HTML_Parse_Tokenization_States, scriptDataEscapedLessThanSignState) {

}

// Section 8.2.4.26
TEST(HTML_Parse_Tokenization_States, scriptDataEscapedEndTagOpenState) {

}

// Section 8.2.4.27
TEST(HTML_Parse_Tokenization_States, scriptDataEscapedEndTagNameState) {

}

// Section 8.2.4.28
TEST(HTML_Parse_Tokenization_States, scriptDataDoubleEscapeStartState) {

}

// Section 8.2.4.29
TEST(HTML_Parse_Tokenization_States, scriptDataDoubleEscapedState) {

}

// Section 8.2.4.30
TEST(HTML_Parse_Tokenization_States, scriptDataDoubleEscapedDashState) {

}

// Section 8.2.4.31
TEST(HTML_Parse_Tokenization_States, scriptDataDoubleEscapedDashDashState) {

}

// Section 8.2.4.32
TEST(HTML_Parse_Tokenization_States, scriptDataDoubleEscapedLessThanSignState) {

}

// Section 8.2.4.33
TEST(HTML_Parse_Tokenization_States, scriptDataDoubleEscapeEndState) {

}

// Section 8.2.4.34
TEST(HTML_Parse_Tokenization_States, beforeAttributeNameState) {

}

// Section 8.2.4.35
TEST(HTML_Parse_Tokenization_States, attributeNameState) {

}

// Section 8.2.4.36
TEST(HTML_Parse_Tokenization_States, beforeAttributeValueState) {

}

// Section 8.2.4.37
TEST(HTML_Parse_Tokenization_States, afterAttributeNameState) {

}

// Section 8.2.4.38
TEST(HTML_Parse_Tokenization_States, attributeValueDoubleQuotedState) {

}

// Section 8.2.4.39
TEST(HTML_Parse_Tokenization_States, attributeValueSingleQuotedState) {

}

// Section 8.2.4.40
TEST(HTML_Parse_Tokenization_States, attributeValueUnquotedState) {

}

// Section 8.2.4.41
TEST(HTML_Parse_Tokenization_States, characterReferenceInAttributeValueState) {

}

// Section 8.2.4.42
TEST(HTML_Parse_Tokenization_States, afterAttributeQuotedState) {

}

// Section 8.2.4.43
TEST(HTML_Parse_Tokenization_States, selfClosingStartTagState) {

}

// Section 8.2.4.44
TEST(HTML_Parse_Tokenization_States, bogusCommentState) {

}

// Section 8.2.4.45
TEST(HTML_Parse_Tokenization_States, markupDeclarationOpenState) {

}

// Section 8.2.4.46
TEST(HTML_Parse_Tokenization_States, commentStartState) {

}

// Section 8.2.4.47
TEST(HTML_Parse_Tokenization_States, commentStartDashState) {

}

// Section 8.2.4.48
TEST(HTML_Parse_Tokenization_States, commentState) {

}

// Section 8.2.4.49
TEST(HTML_Parse_Tokenization_States, commentEndDashState) {

}

// Section 8.2.4.50
TEST(HTML_Parse_Tokenization_States, commentEndState) {

}

// Section 8.2.4.51
TEST(HTML_Parse_Tokenization_States, commentEndBangState) {

}

// Section 8.2.4.52
TEST(HTML_Parse_Tokenization_States, DOCTYPEState) {

}

// Section 8.2.4.53
TEST(HTML_Parse_Tokenization_States, beforeDOCTYPENameState) {

}

// Section 8.2.4.54
TEST(HTML_Parse_Tokenization_States, DOCTYPENameState) {

}

// Section 8.2.4.55
TEST(HTML_Parse_Tokenization_States, afterDOCTYPENameState) {

}

// Section 8.2.4.56
TEST(HTML_Parse_Tokenization_States, afterDOCTYPEPublicKeywordState) {

}

// Section 8.2.4.57
TEST(HTML_Parse_Tokenization_States, beforeDOCTYPEPublicIdentifierState) {

}

// Section 8.2.4.58
TEST(HTML_Parse_Tokenization_States, DOCTYPEPublicIdentifierDoubleQuotedState) {

}

// Section 8.2.4.59
TEST(HTML_Parse_Tokenization_States, DOCTYPEPublicIdentifierSingleQuotedState) {

}

// Section 8.2.4.60
TEST(HTML_Parse_Tokenization_States, afterDOCTYPEPublicIdentifierState) {

}

// Section 8.2.4.61
TEST(HTML_Parse_Tokenization_States, betweenDOCTYPEPublicAndSystemIdentifiersState) {

}

// Section 8.2.4.62
TEST(HTML_Parse_Tokenization_States, afterDOCTYPESystemKeywordState) {

}

// Section 8.2.4.63
TEST(HTML_Parse_Tokenization_States, beforeDOCTYPESystemIdentifierState) {

}

// Section 8.2.4.64
TEST(HTML_Parse_Tokenization_States, DOCTYPESystemIdentifierDoubleQuotedState) {

}

// Section 8.2.4.65
TEST(HTML_Parse_Tokenization_States, DOCTYPESystemIdentifierSingleQuotedState) {

}

// Section 8.2.4.66
TEST(HTML_Parse_Tokenization_States, afterDOCTYPESystemIdentifierState) {

}

// Section 8.2.4.67
TEST(HTML_Parse_Tokenization_States, bogusDOCTYPEState) {

}

// Section 8.2.4.68
TEST(HTML_Parse_Tokenization_States, CDATASectionState) {

}

} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */
