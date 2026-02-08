#include <string>
#include <iostream>
#include <cctype> // for isalpha

#include "algebraic_expressions.hpp"

bool isoperator(char ch)
{
  return ((ch == '+') || (ch == '-') || (ch == '/') || (ch == '*'));
}

int endPost(std::string s, int last)
{
  char ch = s[last];
  if (isalpha(ch))
  {
    return last; // if char at "last" is an operand, then itself is a valid postfix expression,
                 // so the end ("start" idx from left to right) of the postfix expression is just "last"
  }
  else if (isoperator(ch)) // make sure that ch is an operator, otherwise it is an invalid character and should return -1
  {
    int lastEnd = endPost(s, last - 1); // search for the end ("start" idx from left to right)
                                        // of the first <postfix> before ch in the syntax <postfix> <postfix> ch
    if (lastEnd > -1)
    {
      return endPost(s, lastEnd - 1); // search for the end ("start" idx from left to right)
                                      // of the second <postfix> before ch in the syntax <postfix> <postfix> ch
    }
    return -1;
  }
  return -1;
}

bool isPost(std::string s)
{
  int firstChar = endPost(s, s.size() - 1);
  return (firstChar == 0);
  // A postfix expression is valid if and only if the entire string
  // forms a single valid postfix expression (i.e., starts at index 0)
}

void convert(const std::string &postfix, std::string &prefix)
{
  // TODO
}