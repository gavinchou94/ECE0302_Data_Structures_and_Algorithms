#ifndef FINDPALINDROME_HPP
#define FINDPALINDROME_HPP

#include <string>
#include <vector>

class FindPalindrome
{
private:
	/** More private stuff that you define and implement goes here */
	// TODO

	/** @brief findPalindrome internal method
			@attention write this recursive function per the project description.
								You may not change the signature. The method must call itself recursively.
								Failure to follow either of the above two rules will result in a grade of 0 for the project.
			@param currentStringVector  A vector of strings that are currently in the palindrome sentence being built.
			@param candidateStringVector  A vector of strings that are candidates for being in a palindrome sentence.
			@post This method should update the internal data of the FindPalindrome instance as needed.*/
	void recursiveFindPalindromes(std::vector<std::string> candidateStringVector,
																std::vector<std::string> currentStringVector);

	/** @brief internal method to see if a string is a palindrome
			@attention it is provided as a convenience to you but you may use the provided function,
								write your own, or use one of the billions of palindrome functions available on the Internet.
								Note: you probably do not want to use a recursive version for this test (as it is inefficient).
			@param currentString  The string to test if it is a palindrome.
			@return True if the string is a palindrome, false otherwise.*/
	bool isPalindrome(std::string currentString) const;

public:
	/** Constructor for the FindPalindrome object.*/
	FindPalindrome();

	/** Destroys object and frees any memory allocated by object. */
	~FindPalindrome();

	/** @brief Get the current number of sentence palindromes in the FindPalindrome instance.
			@return The integer number of palindromes in the instance. */
	int number() const;

	/** @brief Removes all words from this instance. The internal list of sentence palindromes
						is cleared and any internal data structures are reset.
			@post	The instance contains no words, and the number of sentence palindromes is 0. */
	void clear();

	/** @brief Adds a new string to this FindPalindrome instance and computes the
						number of palindrome sentences possible. Note that the new string must
						be unique per the definition in the project description.
			@post If successful, the string has been added to the FindPalindrome instance,
						and the sentence palindromes in the instance have been recomputed.
			@param value The string to be added to the instance of FindPalindrome.
			@return True if addition was successful (string contains letters only and unique in its case-insensitive form),
							or false if not. */
	bool add(const std::string &value);

	/** @brief Adds a new vector of strings to this FindPalindrome instance and
						computes the number of palindrome sentences possible.
			@attention You may not implement this method by repeatedly calling the add(string) method
								as this would be very inefficient. Implementing this method by repeatedly
								calling add(string) will result in a grade of zero for the project.
			@post If successful, the vector of strings has been added to the FindPalindrome instance,
						and the sentence palindromes for the instance have been recomputed.
			@param stringVector The vector of strings to be added to the instance of FindPalindrome.
			@return True if addition was successful (all strings contain letters only and are unique in their case-insensitive form),
							or false if not. */
	bool add(const std::vector<std::string> &stringVector);

	/** @brief Cut test #1 to see if a palindrome from the vector is possible, if not, no need to go any further.
						A palindrome from the vector of strings is not possible if there are more than
						one char that has an odd number of occurrence.
			@attention See the project description for how this method is to be used.
								You have to call this method when you search
			@param stringVector A vector of strings for which we want to test to see if they could be possibly
						reordered to form a sentence palindrome.
			@pre The string vector should be already valid (for addition conditions)
			@return True if the vector passes the test, false otherwise. */
	bool cutTest1(const std::vector<std::string> &stringVector);

	/** @brief Cut test #2 to see if a palindrome from the vector is possible, if not, no need to go any further.
						We don't know which vector of strings has the fewer number of characters.
						However, for whichever vector of strings has the fewer number of characters, all of those characters
						must appear in the other string vector with more (or an equal) number of each character.
			@example If the string with the fewer number of characters has two 'a's and three 'b's,
							the other string must have at least this number of the characters 'a' and 'b'.
							The count of characters should be case insensitive.
			@attention See the project description for how this method is to be used.
								You have to call this method when you search
			@param stringVector1 A vector of strings.
			@param stringVector2 A vector of strings.
			@return True if the vector passes the test, false otherwise. */
	bool cutTest2(const std::vector<std::string> &stringVector1,
								const std::vector<std::string> &stringVector2);

	/** @brief Return a vector of vectors containing all sentence palindromes.
						Each sentence palindrome is returned as a vector of strings (with orders),
						where the strings include all current strings added to the FindPalindrome instance.
			@attention The order of the sentence palindromes in the returned vector does not matter,
								and the order of the strings in each sentence palindrome vector does matter
								(as it represents the order of the words in the sentence palindrome)
								Also, the sentence palindromes should preserve the case of the strings as they were added
			@return A vector of vectors containing all sentence palindromes. */
	std::vector<std::vector<std::string>> toVector() const;
};

#endif