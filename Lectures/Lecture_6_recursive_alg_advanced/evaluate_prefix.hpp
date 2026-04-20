#include <iostream>
#include <cstdlib>

bool is_operator(char c)
{
  if (c == '+' || c == '-' || c == '*' || c == '/')
  {
    return true;
  }
  return false;
}

bool is_operand(char c)
{
  if (is_operator(c))
  {
    return false;
  }

  return true;
}

int find_prefix_end(std::string s, int startpos)
{
  // from pseudocode of lecture slides
  char c = s[startpos];
  if (is_operand(c))
  {
    // a single operand(i.e., letter) is a valid prefix expression
    return startpos;
  }
  else if (is_operator(c))
  {
    int thisEnd = find_prefix_end(s, startpos + 1); // find the end of the first prefix expression after c
    if (thisEnd >= 0)
    {
      return find_prefix_end(s, thisEnd + 1); // find the end of the second prefix expression after c
      // that concludes the prefix expression range starting at c
    }
    return -1;
  }
  return -1;
}

bool is_valid(std::string s)
{
  int endIndex = find_prefix_end(s, 0);
  char lastChar = s[endIndex];
  if (lastChar >= 0 && endIndex == s.size() - 1)
  {
    return true;
  }
  return false;
}

float eval_expression(float arg1, char op, float arg2)
{
  if (op == '+')
  {
    return arg1 + arg2;
  }
  else if (op == '-')
  {
    return arg1 - arg2;
  }
  else if (op == '*')
  {
    return arg1 * arg2;
  }
  else if (op == '/')
  {
    return arg1 / arg2;
  }

  return 0;
}

float evaluate_prefix(std::string s)
{
  std::size_t s_length = s.size();
  if (s_length == 1)
    return std::stof(s);
  else
  {
    char op = s[0]; // should start with an operator
    // Find the end of the first prefix expression (operand 1)
    int endFirst = find_prefix_end(s, 1);
    // Recursively evaluate this first prefix expression
    float operand1 = evaluate_prefix(s.substr(1, endFirst));
    // Recursively evaluate the second prefix expression (operand 2)
    int endSecond = find_prefix_end(s, endFirst + 1);
    float operand2 = evaluate_prefix(s.substr(endFirst + 1, endSecond));
    return eval_expression(operand1, op, operand2);
  }
}

// Below is the main function that can be used to test using command line inputs

// int main(int argc, char **argv)
// {
//   if (argc != 2)
//   {
//     std::cerr << "Error: " << argv[0] << "requires one argument" << std::endl;
//     return EXIT_FAILURE;
//   }

//   std::string prefix = std::string(argv[1]);

//   if (is_valid(prefix))
//   {
//     float res = evaluate_prefix(prefix);
//     std::cout << res << std::endl;
//   }
//   else
//   {
//     std::cout << "Invalid prefix expression" << std::endl;
//     return EXIT_FAILURE;
//   }

//   return EXIT_SUCCESS;
// }
