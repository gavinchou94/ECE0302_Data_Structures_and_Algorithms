#include <iostream>
#include <string>

/** Writes a character string backward.
 @pre  The string s to write backward.
 @post  None.
 @param s  The string to write backward. */
void writeBackward_re(std::string s)
{
  size_t length = s.size(); // Length of string
  if (length > 0)
  {
    // Write the last character
    std::cout << s.substr(length - 1, 1);

    // Write the rest of the string backward
    writeBackward_re(s.substr(0, length - 1)); // Point A
  } // end if

  // length == 0 is the base case - do nothing
} // end writeBackward_re

/** Iterative version. */
void writeBackward_it(std::string s)
{
  size_t length = s.size();
  while (length > 0)
  {
    std::cout << s.substr(length - 1, 1);
    length--;
  } // end while
} // end writeBackward_it