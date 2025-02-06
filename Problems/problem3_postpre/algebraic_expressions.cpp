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
  int first = 0;
  if (first > last) // invalid index for last
  {
    return -1;
  }

  char ch = s[last];
  if (isalpha(ch))
  {
    return last; // if last is an operator, then the end of the post-fix expression is just itself
  }
  else
  {
    if (isoperator(ch)) // can be omitted, but just to make sure that the last character is an operator
    {
      int lastEnd = endPost(s, last - 1); // search for the "start" (in human eyes) of first post-fix expression before ch
      if (lastEnd > -1)
      {
        return endPost(s, lastEnd - 1); // search for the "start" (in human eyes) of the second post-fix expression before ch
      }
      else
      {
        return -1;
      }
    }
    else
    {
      return -1;
    }
  }
}

bool isPost(std::string s)
{
  int firstChar = endPost(s, s.size() - 1);
  // same as prefix validarity check, postfix expression is valid if and only if
  // the post-fix expression range of the last ch happens to include until the first character
  return (firstChar == 0);
}

void convert(const std::string &postfix, std::string &prefix)
{
  // TODO
}