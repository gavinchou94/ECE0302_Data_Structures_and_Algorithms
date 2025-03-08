/** @file test_array_stack.cpp
 * @author G. Zhou
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "ArrayStack.hpp"
#include "StackInterface.hpp"

TEST_CASE("Testing the Array-Based Stack with push", "[array stack]")
{
   StackInterface<std::string> *stackPtr1 = new ArrayStack<std::string>();
   REQUIRE(stackPtr1->isEmpty() == true);

   std::string items1[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};

   for (int i = 0; i < 10; i++)
   {
      REQUIRE(stackPtr1->push(items1[i]));
   }

   REQUIRE(stackPtr1->isEmpty() == false);
   REQUIRE(stackPtr1->push(items1[10]) == false); // stack is full

   delete stackPtr1;
}

TEST_CASE("Testing the Array-Based Stack with pop", "[array stack]")
{
   StackInterface<std::string> *stackPtr1 = new ArrayStack<std::string>();
   std::string items1[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};

   for (int i = 0; i < 10; i++)
   {
      stackPtr1->push(items1[i]);
   }

   for (int i = 9; i >= 0; i--)
   {
      REQUIRE(stackPtr1->pop()); // Test pop after pushing
   }
   REQUIRE(stackPtr1->isEmpty() == true);
   REQUIRE(stackPtr1->pop() == false); // nothing to pop!
   delete stackPtr1;
}

TEST_CASE("Testing the Array-Based Stack with peek", "[array stack]")
{
   StackInterface<std::string> *stackPtr1 = new ArrayStack<std::string>();
   std::string items1[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten"};

   for (int i = 0; i < 10; i++)
   {
      stackPtr1->push(items1[i]);
      REQUIRE(stackPtr1->peek() == items1[i]); // Test peek after pushing
   }

   for (int i = 9; i >= 0; i--)
   {
      REQUIRE(stackPtr1->peek() == items1[i]); // Test peek after popping
      stackPtr1->pop();
   }
   REQUIRE(stackPtr1->isEmpty() == true);
   REQUIRE_THROWS_AS(stackPtr1->peek(), std::out_of_range); // nothing to peek!
   delete stackPtr1;
}

TEST_CASE("Testing the Array-Based Stack with exceptions", "[array stack]")
{
   StackInterface<std::string> *stackPtr1 = new ArrayStack<std::string>();
   REQUIRE_THROWS_AS(stackPtr1->peek(), std::out_of_range); // nothing to peek!
   REQUIRE_FALSE(stackPtr1->pop());                         // nothing to pop!
   delete stackPtr1;
}

// Write a prefix expression evaluator:
// 1. from the expression, create a stack
// 2. read the expression from right to left
// 3. if the character is an operand, push it to the stack
// 4. if the character is an operator, pop two operands from the stack
// 5. apply the operator to the two operands
// 6. push the result back to the stack
// 7. repeat steps 3-6 until the whole expression is read
// 8. the result is the only element left in the stack
// 9. return the result
// 10. if the stack is empty, throw an runtime exception
// 11. if the stack has more than one element, throw an runtime exception

// Assume the expression is a string of characters
// operands are single digits, and operators are +, -, *, /
int prefix_eval(std::string expression)
{
   StackInterface<int> *stackPtr = new ArrayStack<int>();
   for (int i = expression.length() - 1; i >= 0; i--)
   {
      if (isdigit(expression[i]))
      {
         stackPtr->push(expression[i] - '0');
      }
      else
      {
         int operand1 = 0, operand2 = 0;
         try
         {
            operand1 = stackPtr->peek();
            stackPtr->pop();
         }
         catch (std::out_of_range)
         {
            throw std::runtime_error("Invalid prefix expression due to lack of operands");
         }
         try
         {
            operand2 = stackPtr->peek();
            stackPtr->pop();
         }
         catch (std::out_of_range)
         {
            throw std::runtime_error("Invalid prefix expression due to lack of operands");
         }

         // Apply the operator
         switch (expression[i])
         {
         case '+':
            stackPtr->push(operand1 + operand2);
            break;
         case '-':
            stackPtr->push(operand1 - operand2);
            break;
         case '*':
            stackPtr->push(operand1 * operand2);
            break;
         case '/':
            stackPtr->push(operand1 / operand2);
            break;
         default:
            throw std::invalid_argument("Invalid operator");
         }
      }
   }

   if (stackPtr->isEmpty())
   {
      throw std::runtime_error("Invalid prefix expression");
   }
   int result = stackPtr->peek();

   // One more runtime exception not caught, what is it? And how to write the statements here?

   delete stackPtr;
   return result;
}

TEST_CASE("Testing the prefix expression evaluator", "[prefix expression]")
{
   REQUIRE(prefix_eval("8") == 8);                                 // 8
   REQUIRE(prefix_eval("+34") == 7);                               // 3 + 4
   REQUIRE(prefix_eval("/+532") == 4);                             // (5 + 3) / 2
   REQUIRE(prefix_eval("-+34*29") == -11);                         // (3 + 4) - (2 * 9)
   REQUIRE_THROWS_AS(prefix_eval("?29"), std::invalid_argument);   // Invalid operator
   REQUIRE_THROWS_AS(prefix_eval("+--*1234"), std::runtime_error); // Invalid prefix expression due to lack of operands
   REQUIRE_THROWS_AS(prefix_eval("+"), std::runtime_error);        // Invalid prefix expression due to lack of operands
}

// TODO: write a postfix expression evaluator
// Which step above (in 1~11) in pseudocode will be the only difference between prefix and postfix expression evaluator?

int multi_digit_prefix_eval(std::vector<std::string> expression)
{
   StackInterface<int> *stackPtr = new ArrayStack<int>();
   delete stackPtr;
   return 0;

   // Use std::vector<std::string>, the above code can be easily changed  to allow multi-digit operands
   // briefly discuss the difference between multi-digit implementation and single-digit implementation

   // + 300 – 11 + 5 4 will be 300 + 11 - (5 + 4) = 302
}

// write a bool function to use stack to check if a string is a palindrome
bool is_palindrome(std::string str)
{
   StackInterface<char> *stackPtr = new ArrayStack<char>();
   for (int i = 0; i < str.length() / 2; i++)
   {
      stackPtr->push(str[i]);
   }
   int offset = (str.length() % 2 == 1 ? 1 : 0);
   for (int i = str.length() / 2 + offset; i < str.length(); i++)
   {
      if (char(tolower(stackPtr->peek())) != char(tolower(str[i])))
      {
         delete stackPtr;
         return false;
      }
      stackPtr->pop();
   }
   delete stackPtr;
   return true;
}

TEST_CASE("Testing the palindrome checker", "[palindrome]")
{
   REQUIRE(is_palindrome("Mom") == true);
   REQUIRE(is_palindrome("noon") == true);
   REQUIRE(is_palindrome("kayak") == true);
   REQUIRE(is_palindrome("Pitt") == false);

   REQUIRE(is_palindrome("P") == true); // what happened? any stack operation involved?
   REQUIRE(is_palindrome("") == true);  // what happened? any stack operation involved?

   // Code Comparison: is_palindrome() using stack and is_palindrome() using recursion in Project 2
   // 1. Given that pop() and push() via array are of O(1), is there any difference in time complexity between stack and recursion?
   // 2. What input string would make the stack version slower than the recursion version?  "tomdadmom" or "momdavidmom"
   // 3. What input string would make the stack version faster than the recursion version?  "tomdadmom" or "momdavidmom"
}
