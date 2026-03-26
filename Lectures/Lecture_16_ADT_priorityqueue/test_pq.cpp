/** @file test_pq.cpp
 * @author G. Zhou */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "ArrayPQ.hpp"
#include <iostream>
#include <queue>
#include <random>

TEST_CASE("Test isEmpty() for ArrayPQ", "[ArrayPQ]")
{
   ArrayPQ<int> pq;
   REQUIRE(pq.isEmpty() == true);
}

TEST_CASE("Test add, remove and peek for ArrayPQ", "[ArrayPQ]")
{
   ArrayPQ<int> pq;
   pq.add(3);
   pq.add(1);
   pq.add(2);
   REQUIRE(pq.peek() == 3);
   pq.add(10);
   pq.add(9);
   pq.add(8);

   REQUIRE(pq.peek() == 10);
   pq.remove();
   REQUIRE(pq.peek() == 9);
}

TEST_CASE("Test exception for empty priority queue for ArrayPQ", "[ArrayPQ]")
{
   ArrayPQ<int> pq;
   REQUIRE_THROWS_AS(pq.peek(), std::out_of_range);
   REQUIRE_THROWS_AS(pq.remove(), std::out_of_range);
}

struct OfficeHoursSequence
{
   std::string name;
   int arrivalTime;
   int urgency;

   bool operator<(const OfficeHoursSequence &rhs) const
   {
      if (arrivalTime != rhs.arrivalTime)
         return arrivalTime > rhs.arrivalTime;
      else
         return urgency < rhs.urgency;
   }
};

TEST_CASE("Test add, remove and peek for ArrayPQ with custom type", "[ArrayPQ]")
{
   ArrayPQ<OfficeHoursSequence> pq;
   OfficeHoursSequence s1 = {"Alice", 300, 1};
   OfficeHoursSequence s2 = {"Bob", 300, 2};
   OfficeHoursSequence s3 = {"Charlie", 315, 3};
   OfficeHoursSequence s4 = {"David", 316, 6};
   pq.add(s1);
   pq.add(s2);
   pq.add(s3);
   pq.add(s4);

   // REQUIRE(pq.peek().name == ???);
   pq.remove();
   // REQUIRE(pq.peek().name == ???);
   pq.remove();
   // REQUIRE(pq.peek().name == ???);
   pq.remove();
   // REQUIRE(pq.peek().name == ???);
   pq.remove();
   REQUIRE_THROWS_AS(pq.peek(), std::out_of_range);
}

struct Event
{
   char type;           // 'A' for arrival, 'D' for departure
   int time;            // event time (arrival time or departure time)
   int transactionTime; // only meaningful for arrival events

   // Priority queue returns highest priority first.
   // We want earliest time = highest priority, so earlier time > later time.
   // tie-break: arrival before departure at same time 'A' < 'D'
   bool operator<(const Event &rhs) const { return time > rhs.time || (time == rhs.time && type < rhs.type); }
};

class WaitingLineSimulator
{
public:
   static int numCashiers;

private:
   std::queue<Event> ticketLine;
   int totalTimeWaited;
   int numberServed;
   int numberOfArrivals;
   int availableCashiers;
   int currentTime;

   void processArrival(Event arrivalEvent, ArrayPQ<Event> &eventPQ)
   {
      eventPQ.remove();
      numberOfArrivals++; // count the arrival

      if (availableCashiers > 0)
      {
         int departureTime = currentTime + arrivalEvent.transactionTime;
         eventPQ.add({'D', departureTime, arrivalEvent.transactionTime});
         availableCashiers--;
      }
      else
      {
         ticketLine.push(arrivalEvent);
      }
   }

   void processDeparture(Event departureEvent, ArrayPQ<Event> &eventPQ, bool closedDoor = false)
   {
      eventPQ.remove();
      numberServed++; // count the served customer

      if (!closedDoor && !ticketLine.empty()) // adding the closedDoor condition to prevent serving new customers after closing time
      {
         Event next = ticketLine.front();
         ticketLine.pop();
         int departureTime = currentTime + next.transactionTime;
         int timeWaited = currentTime - next.time;
         totalTimeWaited += timeWaited; // count the waiting time for this customer
         eventPQ.add({'D', departureTime, next.transactionTime});
      }
      else
      {
         availableCashiers++;
      }
   }

public:
   WaitingLineSimulator() : totalTimeWaited(0), numberServed(0), numberOfArrivals(0),
                            availableCashiers(numCashiers), currentTime(0) {}

   void simulate(ArrayPQ<Event> &eventPQ, int duration) // simulate with a pre-built event queue and duration, for testing
   {
      totalTimeWaited = 0;
      numberServed = 0;
      numberOfArrivals = 0;
      availableCashiers = numCashiers;
      currentTime = 0;

      // Clear the ticket line
      while (!ticketLine.empty())
         ticketLine.pop();

      // Event loop: process events until queue is empty or time runs out
      // After duration, stop accepting new arrivals but finish current customers
      bool closedDoor = false;
      int departuresRemaining = 0; // how many busy cashiers still need to finish
      while (!eventPQ.isEmpty())
      {
         Event newEvent = eventPQ.peek();
         currentTime = newEvent.time;

         if (currentTime > duration && newEvent.type == 'A')
         {
            // Past closing time: skip remaining arrivals
            numberOfArrivals++;
            eventPQ.remove();
            continue;
         }

         if (currentTime > duration && !closedDoor)
         {
            closedDoor = true;
            departuresRemaining = numCashiers - availableCashiers; // finish busy cashiers
         }

         if (closedDoor && departuresRemaining <= 0)
            break; // all current customers finished, stop

         if (newEvent.type == 'A')
            processArrival(newEvent, eventPQ);
         else
         {
            processDeparture(newEvent, eventPQ, closedDoor);
            if (closedDoor)
               departuresRemaining--;
         }
      }
   }

   int getTotalTimeWaited() const { return totalTimeWaited; }
   int getNumberServed() const { return numberServed; }
   int getNumberOfArrivals() const { return numberOfArrivals; }
   int getNumberLeftInLine() const { return numberOfArrivals - numberServed; }
   double getAverageWaitTime() const { return (numberServed == 0 ? 0 : (totalTimeWaited + 0.0) / numberServed); }
};

int WaitingLineSimulator::numCashiers = 1;
TEST_CASE("Test WaitingLineSimulator with cashier number", "[WaitingLineSimulator]")
{
   int duration = 90;
   double arrivalProbability = 0.20;
   int maxTransactionTime = 8;

   std::mt19937 generator(2026);                                              // Fixed seed for reproducibility
   std::bernoulli_distribution customerArrives(arrivalProbability);           // True with probability arrivalProbability
   maxTransactionTime = (maxTransactionTime <= 1) ? 1 : maxTransactionTime;   // Ensure maxTransactionTime is at least 1
   std::uniform_int_distribution<int> transactionDist(1, maxTransactionTime); // Uniform distribution for transaction time between 1 and maxTransactionTime

   ArrayPQ<Event> eventPQ;
   for (int clock = 0; clock < duration + 1; clock++)
   {
      if (customerArrives(generator))
      {
         int transactionTime = transactionDist(generator);
         eventPQ.add({'A', clock, transactionTime});
      }
   } // build the event queue with random arrivals and transaction times, save it offline for testing

   WaitingLineSimulator simulator;
   simulator.simulate(eventPQ, duration);

   std::cout << "Number of arrivals: " << simulator.getNumberOfArrivals() << std::endl;
   std::cout << "Number served: " << simulator.getNumberServed() << std::endl;
   std::cout << "Total time waited: " << simulator.getTotalTimeWaited() << std::endl;
   std::cout << "Average wait time: " << simulator.getAverageWaitTime() << std::endl;
}

// Conceptual Question 3:
// Instead of using a priority queue, suppose we manually track each cashier's finish time and
// always peek the next arrival from a queue of arrivals.
// Is a priority queue strictly necessary for this simulation? Could the alternative approach
//     described above produce the same correct results?
// Hint: Compare the time complexity of this event-driven simulation with the time-driven simulation
//     in Lecture 15 (test_queue.cpp) in terms of the number of events E and the duration of the simulation ticks T
//      Under what conditions does event-driven significantly win?