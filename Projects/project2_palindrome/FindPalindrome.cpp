#include <string>
#include <vector>
#include <iostream>
#include "FindPalindrome.hpp"

//------------------- HELPER FUNCTIONS -----------------------------------------
// non-class helper functions go here, should be declared as "static"

// helper non-member function to convert string to lower case
static void convertToLowerCase(std::string &value)
{
	for (int i = 0; i < value.size(); i++)
	{
		value[i] = std::tolower(value[i]);
	}
} // finished

//------------------- PRIVATE CLASS METHODS ------------------------------------

// private function to determine if a string is a palindrome
bool FindPalindrome::isPalindrome(std::string currentString) const
{
	// make sure that the string is lower case
	convertToLowerCase(currentString);
	// see if the characters are symmetric
	int stringLength = currentString.size();
	for (int i = 0; i < stringLength / 2; i++)
	{
		if (currentString[i] != currentString[stringLength - i - 1])
		{
			return false;
		}
	}
	return true;
} // finished

// private recursive function. Must use this signature!
void FindPalindrome::recursiveFindPalindromes(std::vector<std::string> candidateStringVector,
																							std::vector<std::string> currentStringVector)
{
	// TODO
	return;
}

//------------------- PUBLIC CLASS METHODS -------------------------------------

FindPalindrome::FindPalindrome()
{
	// TODO
}

FindPalindrome::~FindPalindrome()
{
	// TODO
}

int FindPalindrome::number() const
{
	// TODO
	return -1;
}

void FindPalindrome::clear()
{
	// TODO
}

bool FindPalindrome::cutTest1(const std::vector<std::string> &stringVector)
{
	// TODO
	return false;
}

bool FindPalindrome::cutTest2(const std::vector<std::string> &stringVector1,
															const std::vector<std::string> &stringVector2)
{
	// TODO
	return false;
}

bool FindPalindrome::add(const std::string &value)
{
	// TODO
	return false;
}

bool FindPalindrome::add(const std::vector<std::string> &stringVector)
{
	// TODO
	return false;
}

std::vector<std::vector<std::string>> FindPalindrome::toVector() const
{
	// TODO
	return std::vector<std::vector<std::string>>();
}