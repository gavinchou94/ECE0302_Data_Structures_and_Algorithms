// Project 3 -- XML Parser

/** @file XMLParser.cpp */

#include <string>
#include "XMLParser.hpp"

XMLParser::XMLParser()
{
	// TODO
} // end default constructor

// Then finish this function to pass the 4th~6th unit tests
bool XMLParser::tokenizeInputString(const std::string &inputString)
{
	// TODO, use '<' and '>' as anchors to scan string; Remember to clear each time before
	// tokenizing a new string, and refer to the following code structure:

	// for (char c : inputString)
	// {
	// 	if (c == '<') {?? continue;}
	// 	else if (c == '>') {?? continue;}
	// 	else {?? continue;}
	// }

	return false;
} // end

// Then finish this function to pass the 7th~9th unit test
bool XMLParser::parseTokenizedInput()
{
	// TODO, iterate through tokenizedInputVector to check validity
	// and update stack and bag accordingly, and refer to the following code structure:

	// for (int i = 0; i < tokenizedInputVector.size(); i++)
	// {
	//   if (?? == START_TAG) {?? continue;}
	// 	 else if (?? == END_TAG) {?? continue;}
	// 	 else if (?? == EMPTY_TAG) {?? continue;}
	// 	 ...
	// }

	return false;
}

void XMLParser::clear()
{
	// TODO
}

std::vector<TokenStruct> XMLParser::returnTokenizedInput() const
{
	return tokenizedInputVector;
}

bool XMLParser::containsElementName(const std::string &element) const
{
	// TODO
	return false;
}

int XMLParser::frequencyElementName(const std::string &element) const
{
	// TODO
	// Throw std::logic_error if either tokenizeInputString() or parseTokenizedInput() returns false
	// If Bag is updated correctly, this should be as simple as one line.

	return -1;
}
