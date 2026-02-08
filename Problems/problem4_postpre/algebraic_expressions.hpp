/** Functions for testing and converting postfix expressions.
 * @file algebraic_expressions.hpp */

#ifndef _ALGEBRAICEXPRESSIONS_HPP_
#define _ALGEBRAICEXPRESSIONS_HPP_

#include <string>

/** Determine if a character is a valid operator.
 * @param ch character to check for operator
 * @return true if ch is one of +*-/ false otherwise */
bool isoperator(char ch);

/** Return index to the "end" of a valid postfix expression
 * given the index of the last character. Note that because
 * postfix expressions are formatted <postfix> <postfix> <operator>
 * the end of the expression is where the first <postfix> starts.
 * For example, endPost("ab+",2) returns 0.
 * Passing in an operand will return the input index directly.
 * @param s string postfix expression
 * @param last the index of the last character of the expression
 * @return index of the "end" of the postfix expression, or -1 if an input is invalid
 * @attention the "end" literally means "start",
 *            i.e., the index of the first character of the first <postfix> */
int endPost(std::string s, int last);

/** Determine if the string s is a valid postfix expression.
 * @param s string expression
 * @return true if s is a valid postfix expression, false if not */
bool isPost(std::string s);

/** Convert the input postfix expression to prefix notation.
 * @param postfix string postfix expression to convert
 * @param prefix string reference to be used to store the prefix expression
 *       it is called with a initially empty string and will be modified by the function
 * @throw std::invalid_argument if postfix is not a valid expression
 * @post prefix contains the converted expression */
void convert(const std::string &postfix, std::string &prefix);

#endif