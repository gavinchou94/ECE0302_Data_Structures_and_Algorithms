/** @file test_array_stack.cpp
 * @author G. Zhou */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "ArrayStack.hpp"
#include "StackInterface.hpp"

TEST_CASE("Testing the Array-Based Stack with push", "[array stack]")
{
   StackInterface<std::string> *stackPtr1 = new ArrayStack<std::string>();
   REQUIRE(stackPtr1->isEmpty() == true);

   std::string items1[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
                           "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen", "twenty"};

   for (int i = 0; i < 20; i++)
   {
      REQUIRE(stackPtr1->push(items1[i]));
   }

   REQUIRE(stackPtr1->isEmpty() == false);
   REQUIRE(stackPtr1->push(items1[20]) == false); // stack is full

   delete stackPtr1;
}

TEST_CASE("Testing the Array-Based Stack with pop", "[array stack]")
{
   StackInterface<std::string> *stackPtr1 = new ArrayStack<std::string>();

   std::string items1[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
                           "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

   for (int i = 0; i < 20; i++)
   {
      stackPtr1->push(items1[i]);
   }

   for (int i = 19; i >= 0; i--)
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

   std::string items1[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
                           "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};

   for (int i = 0; i < 20; i++)
   {
      stackPtr1->push(items1[i]);
      REQUIRE(stackPtr1->peek() == items1[i]); // Test peek after pushing
   }

   for (int i = 19; i >= 0; i--)
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

   // TODO: One more runtime exception should be caught to make sure the expression is valid.
   // And how to write the code to throw the exception? Hint: Check the last REQUIRE statement in the test case below.
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
   // REQUIRE_THROWS_AS(prefix_eval("+345"), std::runtime_error);     // Invalid prefix expression due to what?
}

int multi_digit_prefix_eval(std::vector<std::string> expression)
{
   StackInterface<int> *stackPtr = new ArrayStack<int>();
   delete stackPtr;
   return 0;

   // Use std::vector<std::string>, the above code can be easily modified to allow multi-digit operands
}

// bool function to use stack to check if a string is a palindrome
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
   // 1. Given that pop() and push() via array are of O(1), is there any major difference in time complexity between stack and recursion?
   // 2. What input string would make the stack version slower than the recursion version?  "tomdadmom" or "momdavidmom"
   // 3. What input string would make the stack version faster than the recursion version?  "tomdadmom" or "momdavidmom"
}

struct Room
{
   int row, col;
   bool operator==(const Room &rhs) const { return row == rhs.row && col == rhs.col; }
   bool operator!=(const Room &rhs) const { return !(*this == rhs); }
};

using Maze = std::vector<std::vector<char>>;    // typedef for readability
using Path = std::vector<std::string>;          // typedef for readability
using Stack = ArrayStack<Room>;                 // typedef for readability
using Visited = std::vector<std::vector<bool>>; // typedef for readability
const Room NO_PATH = {-1, -1};

// Marks a room as visited in the visitedRooms 2D vector.
void markVisited(Room someRoom, Visited &visitedRooms)
{
   visitedRooms[someRoom.row][someRoom.col] = true;
}

// Clears visited marks on all rooms.
void unvisitAll(Visited &visitedRooms)
{
   const int MAZE_ROWS = visitedRooms.size();
   const int MAZE_COLS = visitedRooms[0].size();
   for (int row = 0; row < MAZE_ROWS; ++row)
   {
      for (int col = 0; col < MAZE_COLS; ++col)
      {
         visitedRooms[row][col] = false;
      }
   }
}

// Returns the next unvisited room, if any, that is adjacent to a given room.
// Returns a sentinel value, NO_PATH, if no unvisited adjacent room was found.
Room getNextRoom(Room fromRoom, const Visited &visitedRooms, const Maze &mazeLayout)
{
   const int MAZE_ROWS = visitedRooms.size();
   const int MAZE_COLS = visitedRooms[0].size();
   const int rowOffsets[4] = {-1, 1, 0, 0};
   const int colOffsets[4] = {0, 0, 1, -1};

   for (int direction = 0; direction < 4; ++direction)
   {
      int nextRow = fromRoom.row + rowOffsets[direction];
      int nextCol = fromRoom.col + colOffsets[direction];

      bool withinMaze = nextRow >= 0 && nextRow < MAZE_ROWS && nextCol >= 0 && nextCol < MAZE_COLS;
      if (withinMaze && mazeLayout[nextRow][nextCol] == 'o' && !visitedRooms[nextRow][nextCol])
      {
         return {nextRow, nextCol};
      }
   }
   return NO_PATH;
}

void printStack(Stack &stack)
{
   Stack tempStack;
   while (!stack.isEmpty())
   {
      Room room = stack.peek();
      std::cout << "(" << room.row + 1 << "," << room.col + 1 << ") ";
      tempStack.push(room);
      stack.pop();
   }
   std::cout << std::endl;

   // Restore the original stack
   while (!tempStack.isEmpty())
   {
      stack.push(tempStack.peek());
      tempStack.pop();
   }
}

/** Tests whether a sequence of paths exists between two rooms. Nonrecursive stack version.
 * @pre entranceRoom and exitRoom both exist in the maze.
 * @post Rooms visited during the search are marked as visited in the maze .
 * @param entranceRoom The origin room.
 * @param exitRoom The destination room.
 * @return True if a sequence of paths exists from entranceRoom to exitRoom; otherwise returns false. */
bool searchWithStack(Room entranceRoom, Room exitRoom, const Maze &mazeLayout, Visited &visitedRooms, Path &finalPath)
{
   Stack pathStack;
   unvisitAll(visitedRooms);     // Clear marks on all rooms
   pathStack.push(entranceRoom); // Push entrance room onto pathStack and mark it as visited
   finalPath.push_back(
       "(" + std::to_string(entranceRoom.row + 1) +
       "," + std::to_string(entranceRoom.col + 1) +
       ")");                                // Add entrance room to final path
   markVisited(entranceRoom, visitedRooms); // Mark entrance room as visited
   printStack(pathStack);                   // print the stack after pushing the entrance room
   Room currentRoom = pathStack.peek();

   while (!pathStack.isEmpty() && (currentRoom != exitRoom))
   // The stack contains a directed path from the entrance room to the room at the top of the stack
   // i.e., a path from the bottom of the stack to the room at the top of the stack
   {
      // Find an unvisited room adjacent to the room on the top of the stack
      Room nextRoom = getNextRoom(currentRoom, visitedRooms, mazeLayout);
      if (nextRoom == NO_PATH)
      {
         pathStack.pop();      // No room found; backtrack
         finalPath.pop_back(); // Remove the backtracked room from the final path
      }
      else
      {
         // Visit nextRoom and push it onto the stack
         pathStack.push(nextRoom);
         markVisited(nextRoom, visitedRooms);
         finalPath.push_back("(" + std::to_string(nextRoom.row + 1) + "," + std::to_string(nextRoom.col + 1) + ")"); // Add nextRoom to final path
      }
      if (!pathStack.isEmpty())
      {
         currentRoom = pathStack.peek();
      }
      printStack(pathStack);
   } // end while
   return !pathStack.isEmpty();
} // end searchWithStack

TEST_CASE("Testing the stack-based maze search", "[stack maze]")
{
   Maze mazeLayout = {
       {'o', 'x', 'o', 'o', 'o'},
       {'o', 'x', 'o', 'x', 'o'},
       {'o', 'x', 'o', 'x', 'o'},
       {'o', 'o', 'o', 'x', 'o'},
       {'o', 'x', 'x', 'x', 'o'}};

   const int MAZE_ROWS = mazeLayout.size();
   const int MAZE_COLS = mazeLayout[0].size();
   Visited visitedRooms(MAZE_ROWS, std::vector<bool>(MAZE_COLS, false));
   Path p;
   REQUIRE(searchWithStack({0, 0}, {4, 4}, mazeLayout, visitedRooms, p) == true);
   // Verify that backtracking occurs via its absence in the final path and its true value in visitedRooms
   REQUIRE(std::find(p.begin(), p.end(), "(5,1)") == p.end()); // backtracking occurs at (5,1)
   REQUIRE(visitedRooms[5 - 1][1 - 1] == true);                // backtracking occurs at (5,1)
}