/** @file test_queue.cpp
 * @author G. Zhou */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "ArrayQueue.hpp"
#include "RingDeque.hpp"
#include "LinkedDeque.hpp"
#include "evaluate_postfix.hpp"
#include <iostream>
#include <random>
#include <stdexcept>
#include <cctype>
#include <queue>
#include <stack>

TEST_CASE("Test isEmpty() for ArrayQueue", "[ArrayQueue]")
{
   ArrayQueue<int> queue;
   REQUIRE(queue.isEmpty() == true);
}

TEST_CASE("Test enqueue() and peekFront() for ArrayQueue", "[ArrayQueue]")
{
   ArrayQueue<int> queue;
   queue.enqueue(1);
   queue.enqueue(2);
   queue.enqueue(3);
   REQUIRE(queue.peekFront() == 1);
   queue.enqueue(4);
   queue.enqueue(5);
   queue.enqueue(6);
   queue.enqueue(7);
   queue.enqueue(8);
   queue.enqueue(9);
   queue.enqueue(10);
   REQUIRE_THROWS_AS(queue.enqueue(11), std::logic_error);
}

TEST_CASE("Test dequeue() and peekFront() for ArrayQueue", "[ArrayQueue]")
{
   ArrayQueue<int> queue;
   for (int i = 1; i <= 10; ++i)
   {
      queue.enqueue(i);
   }
   REQUIRE(queue.peekFront() == 1);
   REQUIRE_THROWS_AS(queue.enqueue(11), std::logic_error);

   queue.dequeue();
   REQUIRE(queue.peekFront() == 2);
   REQUIRE_NOTHROW(queue.enqueue(11));

   queue.dequeue();
   REQUIRE(queue.peekFront() == 3);
   queue.dequeue();
   REQUIRE(queue.peekFront() == 4);
}

TEST_CASE("Test exception for empty queue for ArrayQueue", "[ArrayQueue]")
{
   ArrayQueue<int> queue;
   REQUIRE_THROWS_AS(queue.dequeue(), std::logic_error);
   REQUIRE_THROWS_AS(queue.peekFront(), std::logic_error);
}

class Customer
{
private:
   int arrivalTime;
   int transactionTime;
   int customerNumber;

public:
   Customer() : arrivalTime(0), transactionTime(0), customerNumber(0) {}
   Customer(int arrival, int transaction, int number) : arrivalTime(arrival), transactionTime(transaction), customerNumber(number) {}

   int getArrivalTime() const { return arrivalTime; }
   int getTransactionTimeLeft() const { return transactionTime; }
   int getCustomerNumber() const { return customerNumber; }
};

class WaitingLineSimulator
{
private:
   ArrayQueue<Customer> line;
   int totalTimeWaited;
   int numberServed;
   int numberOfArrivals;

public:
   WaitingLineSimulator() : totalTimeWaited(0), numberServed(0), numberOfArrivals(0) {}

   void simulate(int duration, double arrivalProbability, int maxTransactionTime)
   {
      totalTimeWaited = 0;
      numberServed = 0;
      numberOfArrivals = 0;
      Customer currentServing;
      int transactionTimeLeft = 0;

      std::mt19937 generator(2026);                                              // Fixed seed for reproducibility
      std::bernoulli_distribution customerArrives(arrivalProbability);           // True with probability arrivalProbability
      maxTransactionTime = (maxTransactionTime <= 1) ? 1 : maxTransactionTime;   // Ensure maxTransactionTime is at least 1
      std::uniform_int_distribution<int> transactionDist(1, maxTransactionTime); // Uniform distribution for transaction time between 1 and maxTransactionTime

      for (int clock = 0; clock < duration + 1; clock++) // Tick every minute
      {
         if (clock % 10 == 0) // Print the state of the simulation every 10 minutes
         {
            std::cout << "Current Time Stamp (the start of): " << clock << " min" << std::endl;
            if (transactionTimeLeft > 0 || currentServing.getCustomerNumber() > 0)
            {
               std::cout << "Current serving -> customerNumber: " << currentServing.getCustomerNumber()
                         << ", arrivalTime: " << currentServing.getArrivalTime()
                         << ", transactionTime: " << currentServing.getTransactionTimeLeft()
                         << ", transactionTimeLeft: " << (transactionTimeLeft > 0 ? std::to_string(transactionTimeLeft) : "0 (this customer was just finished)")
                         << std::endl;
               if (transactionTimeLeft == 0)
               {
                  currentServing = Customer(); // Reset to idle for the purpose of printing the state
               }
            }
            else
            {
               std::cout << "Current serving -> none" << std::endl;
            }

            std::cout << "Waiting line -> ";
            int waitingCount = numberOfArrivals - numberServed;
            if (waitingCount <= 0)
            {
               std::cout << "empty" << std::endl;
            }
            else
            {
               std::cout << std::endl;
               ArrayQueue<Customer> lineCopy = line; // Create a copy of the line to iterate through
               for (int i = 0; i < waitingCount; i++)
               {
                  Customer customer = lineCopy.peekFront();
                  lineCopy.dequeue();
                  lineCopy.enqueue(customer);

                  std::cout << "  customerNumber: " << customer.getCustomerNumber()
                            << ", arrivalTime: " << customer.getArrivalTime()
                            << ", transactionTime: " << customer.getTransactionTimeLeft()
                            << std::endl;
               }
            }
            std::cout << std::endl;
         }

         if (customerArrives(generator)) // A new customer arrives
         {
            numberOfArrivals++;
            int transactionTime = transactionDist(generator);
            Customer nextArrival(clock, transactionTime, numberOfArrivals); // Customer object creation
            line.enqueue(nextArrival);
         }
         if (transactionTimeLeft > 0) // If the current customer is still being served
         {
            transactionTimeLeft--;
         }
         else if (!line.isEmpty())
         {
            Customer nextCustomer = line.peekFront();
            line.dequeue();

            transactionTimeLeft = nextCustomer.getTransactionTimeLeft() - 1;
            currentServing = nextCustomer;
            int timeWaited = clock - nextCustomer.getArrivalTime();
            totalTimeWaited += timeWaited;
            numberServed++;
         }
      }
   }

   int getTotalTimeWaited() const { return totalTimeWaited; }
   int getNumberServed() const { return numberServed; }
   int getNumberOfArrivals() const { return numberOfArrivals; }
   int getNumberLeftInLine() const { return numberOfArrivals - numberServed; }
   double getAverageWaitTime() const { return (numberServed == 0 ? 0 : (totalTimeWaited + 0.0) / numberServed); }
};

TEST_CASE("Test WaitingLineSimulator with ArrayQueue", "[WaitingLineSimulator]")
{
   WaitingLineSimulator simulator;

   // Simulate for 90 minutes, with a 20% chance of a new customer arriving each minute
   // and a maximum transaction time of 8 minutes.
   simulator.simulate(90, 0.20, 8);

   std::cout << "Number of arrivals: " << simulator.getNumberOfArrivals() << std::endl;
   std::cout << "Number served: " << simulator.getNumberServed() << std::endl;
   std::cout << "Total time waited: " << simulator.getTotalTimeWaited() << std::endl;
   std::cout << "Average wait time: " << simulator.getAverageWaitTime() << std::endl;
}

int precedence(char op)
{
   if (op == '+' || op == '-')
      return 1;
   if (op == '*' || op == '/')
      return 2;
   return 0;
}

std::string infixToPostfix(const std::string &infix)
{
   std::queue<char> postfixExpQueue;
   std::stack<char> operatorStack;

   for (char currentChar : infix)
   {
      if (std::isspace(currentChar))
      {
         continue;
      }

      if (std::isalnum(currentChar))
      {
         postfixExpQueue.push(currentChar);
      }
      else if (currentChar == '(')
      {
         operatorStack.push(currentChar);
      }
      else if (is_operator(currentChar))
      {
         while (!operatorStack.empty() && operatorStack.top() != '(' &&
                precedence(currentChar) <= precedence(operatorStack.top()))
         {
            postfixExpQueue.push(operatorStack.top());
            operatorStack.pop();
         }
         operatorStack.push(currentChar);
      }
      else if (currentChar == ')')
      {
         while (!operatorStack.empty() && operatorStack.top() != '(')
         {
            postfixExpQueue.push(operatorStack.top());
            operatorStack.pop();
         }

         if (!operatorStack.empty() && operatorStack.top() == '(')
         {
            operatorStack.pop();
         }
      }
   }

   while (!operatorStack.empty())
   {
      if (operatorStack.top() != '(')
      {
         postfixExpQueue.push(operatorStack.top());
      }
      operatorStack.pop();
   }

   std::string postfixExp;
   while (!postfixExpQueue.empty())
   {
      postfixExp.push_back(postfixExpQueue.front());
      postfixExpQueue.pop();
   }

   return postfixExp;
}

TEST_CASE("Test infix to postfix using std queue/stack", "[InfixPostfix]")
{
   REQUIRE(infixToPostfix("A+B*(C-D)") == "ABCD-*+");
   REQUIRE(infixToPostfix("(A+B)/C") == "AB+C/");
   REQUIRE(infixToPostfix("a-(b+c*d)/e") == "abcd*+e/-");

   // passing to two functions, you create your own infix algebric exp calculator
   REQUIRE(evaluate_postfix(infixToPostfix("3-(1+8*6)/7")) == 3 - (1 + 8 * 6) / 7);
   // 3 * 4 - (1 + 8 * 6) / 7) will be converted to "34*186*+7/-" and evaluated to 3 * 4 - (1 + 8 * 6) / 7
   REQUIRE(evaluate_postfix(infixToPostfix("3 * 4 - (1 + 8 * 6) / 7)")) == 3 * 4 - (1 + 8 * 6) / 7);
}

TEST_CASE("Test isEmpty() for RingDeque", "[RingDeque]")
{
   RingDeque<int> deque;
   REQUIRE(deque.isEmpty() == true);
}

TEST_CASE("Test enqueue, deque and peek for RingDeque", "[RingDeque]")
{
   RingDeque<int> deque;
   deque.enqueue_front(1);
   deque.enqueue_front(2);
   deque.enqueue_front(3);
   REQUIRE(deque.peekFront() == 3);
   REQUIRE(deque.peekBack() == 1);

   deque.enqueue_back(4);
   deque.enqueue_back(5);
   deque.enqueue_back(6);
   REQUIRE(deque.peekFront() == 3);
   REQUIRE(deque.peekBack() == 6);

   deque.dequeue_front();
   REQUIRE(deque.peekFront() == 2);

   deque.dequeue_back();
   REQUIRE(deque.peekBack() == 5);
}

TEST_CASE("Test capacity for RingDeque", "[RingDeque]")
{
   RingDeque<int> deque;
   for (int i = 1; i <= 10; ++i)
   {
      deque.enqueue_back(i);
   }
   REQUIRE(deque.peekFront() == 1);
   REQUIRE(deque.peekBack() == 10);

   for (int i = 11; i <= 20; ++i)
   {
      deque.enqueue_front(i);
   }
   REQUIRE(deque.peekFront() == 20);
   REQUIRE(deque.peekBack() == 10);

   // TODO: Add a breakpoint here to check the deque's state.
   // What are the values of front, back, and count?
   // What is stored in the array from items[0] to items[19]?
   REQUIRE_THROWS_AS(deque.enqueue_back(21), std::logic_error);
   REQUIRE_THROWS_AS(deque.enqueue_front(21), std::logic_error);

   REQUIRE(deque.isFull() == true);
}

TEST_CASE("Test exception for empty deque for RingDeque", "[RingDeque]")
{
   RingDeque<int> deque;
   REQUIRE(deque.isEmpty() == true);
   REQUIRE(deque.isFull() == false);
   REQUIRE_THROWS_AS(deque.dequeue_front(), std::logic_error);
   REQUIRE_THROWS_AS(deque.dequeue_back(), std::logic_error);
   REQUIRE_THROWS_AS(deque.peekFront(), std::logic_error);
   REQUIRE_THROWS_AS(deque.peekBack(), std::logic_error);
}

TEST_CASE("Test LinkedDeque operations", "[LinkedDeque]")
{
   LinkedDeque<int> deque;
   REQUIRE(deque.isEmpty() == true);

   deque.enqueue_front(1);
   deque.enqueue_front(2);
   deque.enqueue_front(3);
   REQUIRE(deque.peekFront() == 3);
   REQUIRE(deque.peekBack() == 1);

   deque.enqueue_back(4);
   deque.enqueue_back(5);
   deque.enqueue_back(6);
   REQUIRE(deque.peekFront() == 3);
   REQUIRE(deque.peekBack() == 6);

   deque.dequeue_front();
   REQUIRE(deque.peekFront() == 2);

   deque.dequeue_back();
   REQUIRE(deque.peekBack() == 5);

   // Test exception for empty deque
   LinkedDeque<int> emptyDeque;
   REQUIRE(emptyDeque.isEmpty() == true);
   REQUIRE(emptyDeque.isFull() == false);
   REQUIRE_THROWS_AS(emptyDeque.dequeue_front(), std::logic_error);
   REQUIRE_THROWS_AS(emptyDeque.dequeue_back(), std::logic_error);
   REQUIRE_THROWS_AS(emptyDeque.peekFront(), std::logic_error);
   REQUIRE_THROWS_AS(emptyDeque.peekBack(), std::logic_error);

   // Test capacity for LinkedDeque
   LinkedDeque<int> deque2;
   for (int i = 1; i <= 10; ++i)
   {
      deque2.enqueue_back(i);
   }
   REQUIRE(deque2.peekFront() == 1);
   REQUIRE(deque2.peekBack() == 10);

   for (int i = 11; i <= 20; ++i)
   {
      deque2.enqueue_front(i);
   }
   REQUIRE(deque2.peekFront() == 20);
   REQUIRE(deque2.peekBack() == 10);

   REQUIRE_NOTHROW(deque2.enqueue_back(21));
   REQUIRE_NOTHROW(deque2.enqueue_front(21));

   REQUIRE(deque2.isFull() == false);
}

// Demo of using Deque to implement a Stack and a Queue
// That is how standard library's std::stack and std::queue are
// implemented under the hood (using std::deque as the underlying container by default).

template <typename T>
class Adaptor1UsingDeque
{
private:
   LinkedDeque<T> deque;

public:
   void op1(T value) { deque.enqueue_front(value); }
   void op2() { deque.dequeue_front(); }
   T op3() const { return deque.peekFront(); }
   bool isEmpty() const { return deque.isEmpty(); }
};

template <typename T>
class Adaptor2UsingDeque
{
private:
   LinkedDeque<T> deque;

public:
   void op1(T value) { deque.enqueue_back(value); }
   void op2() { deque.dequeue_front(); }
   T op3() const { return deque.peekFront(); }
   bool isEmpty() const { return deque.isEmpty(); }
};

TEST_CASE("Test adaptors using LinkedDeque", "[AdaptorUsingDeque]")
{
   Adaptor1UsingDeque<int> adaptor1;
   // feel free to test yourself by adding more operations here
   REQUIRE(adaptor1.isEmpty() == true);

   Adaptor2UsingDeque<int> adaptor2;
   // feel free to test yourself by adding more operations here
   REQUIRE(adaptor2.isEmpty() == true);
}

// TODO: Explore to determine which adaptor is implementing a stack and which one is implementing a queue.
// and determine the name of the operations (op1, op2, op3) for each adaptor.
// Candidates are push, pop, top for stack; and enqueue, dequeue, peek for queue.