#include <string>

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

int find_postfix_start(std::string s, int endpos)
{
  char c = s[endpos];
  if (is_operand(c))
  {
    return endpos;
  }
  else if (is_operator(c))
  {
    int secondStart = find_postfix_start(s, endpos - 1);
    if (secondStart >= 0)
    {
      return find_postfix_start(s, secondStart - 1);
    }
    return -1;
  }
  return -1;
}

bool is_valid(std::string s)
{
  int startIndex = find_postfix_start(s, s.size() - 1);
  char firstChar = s[startIndex];
  if (firstChar >= 0 && startIndex == 0)
  {
    return true;
  }
  return false;
}

float evaluate_postfix(std::string s)
{
  int s_length = s.size();
  if (s_length == 1)
    return std::stof(s);
  else
  {
    char op = s[s_length - 1];
    int startSecond = find_postfix_start(s, s_length - 2);
    float operand2 = evaluate_postfix(s.substr(startSecond, s_length - 1 - startSecond));
    int startFirst = find_postfix_start(s, startSecond - 1);
    float operand1 = evaluate_postfix(s.substr(startFirst, startSecond - startFirst));
    return eval_expression(operand1, op, operand2);
  }
}