/** @file test_boxes.cpp
 * @author G. Zhou
 * @copyright 2026 ECE 0302
 * @brief Test cases for the Box classes, with illustrations on polymorphism, operator overloading
 */

#define CATCH_CONFIG_MAIN
#include "BoxInterface.hpp"
#include "PlainBox.hpp"
#include "ToyBox.hpp"
#include "MagicBox.hpp"
#include "AddingBox.hpp"

#include "catch.hpp"

TEST_CASE("1. Test ENUM in ToyBox", "[ToyBox]")
{
   ToyBox<int> box1(3, YELLOW); // 3 is the item, YELLOW is the color

   // enum GREEN is stored as 3,  YELLOW is 4, so the following tests are valid
   REQUIRE(box1.getItem() == 3);
   REQUIRE(box1.getItem() == GREEN);
   REQUIRE(box1.getColor() == YELLOW);
   REQUIRE(box1.getColor() == 4);
}

TEST_CASE("2. Test storing static pointer in PlainBox", "[PlainBox]")
{
   PlainBox<int *> pbox;
   int x[3] = {1, 2, 3}; // x is an array of 3 integers, but stored as a pointer
   int y[3] = {1, 2, 3}; // y is also stored as a pointer
   pbox.setItem(x);
   REQUIRE(pbox.getItem() == x);
   REQUIRE(pbox.getItem() != y); // comparing pointers, try run VS Code debugger to see the memory addresses
}

TEST_CASE("3. Test base type pointer referencing to a derived object", "[Binding]")
{
   PlainBox<int> *box1 = new ToyBox<int>(100, RED);
   PlainBox<int> *box2 = new MagicBox<int>(302);

   // box1->getColor(); // TODO: explain why this line would not compile?
   REQUIRE(box1->getItem() == 100);
   REQUIRE(box2->getItem() == 302);

   box1->setItem(200);
   REQUIRE(box1->getItem() == 200); // dynamic binding happens here, ToyBox set item to be 200

   box2->setItem(402);
   REQUIRE(box2->getItem() == 302); // dynamic binding also happens here, magic takes effective

   // TODO: something is here after we finishing using box1, box2, what is it?

   PlainBox<std::string> pbox;
   pbox = MagicBox<std::string>("Pitfall");
   pbox.setItem("Shock");
   REQUIRE(pbox.getItem() == "Shock"); // Magic doesn't happen here. The binding occurs at compile time
                                       // since this is not a pointer or reference.
                                       // Refer to Lecture 2, Slide 17
}

// Examples for Lecture 2, Slide 16
class Shape
{
public:
   virtual void print() = 0;
};
class Rectangle : public Shape
{
public:
   void print() { std::cout << "I am a rectangle" << std::endl; }
};
class Circle : public Shape
{
public:
   void print() { std::cout << "I am a circle" << std::endl; }
};

void funct1(Shape *x) { std::cout << "I called funct1" << std::endl; }

TEST_CASE("4. Test Dynamic Memory and Polymorphism", "[Shape]")
{
   PlainBox<Shape *> b;        // PlainBox storing pointers to base class
   b.setItem(new Rectangle()); // set to a new derived object
   b.getItem()->print();       // verify the object is a Rectangle

   b.setItem(new Circle()); // set to another derived object
   b.getItem()->print();    // verify the object is a Circle

   // Above example suggests that polymorphism can help use unified interface to
   // access different type of derived class

   Shape *ptr = new Circle();
   funct1(ptr); // This can compile since when using base class pointer as function/method argument type
                // the derived class object can be passed in
}

TEST_CASE("5. Test add operator in AddingBox", "[AddingBox]")
{
   // int: 1 + 2 = 3
   AddingBox<int> addBox1A(1), addBox1B(2);
   AddingBox<int> sumBox1 = addBox1A + addBox1B; // both copy constructor and + operator are called
   REQUIRE(sumBox1.getItem() == 3);

   // long: 111111L + 888888L = 999999L
   AddingBox<long> addBox2A(111111L), addBox2B(888888L);
   AddingBox<long> sumBox2 = addBox2A + addBox2B;
   REQUIRE(sumBox2.getItem() == 999999L);

   // std::string "2" + "3" = "23"
   AddingBox<std::string> addBox3A("2"), addBox3B("3");
   AddingBox<std::string> sumBox3 = addBox3A + addBox3B;
   REQUIRE(sumBox3.getItem() == "23");

   // char: '2' + '3' = 'e'
   AddingBox<char> addBox4A('2'), addBox4B('3');
   AddingBox<char> sumBox4 = addBox4A + addBox4B;
   REQUIRE(sumBox4.getItem() == 'e');

   // double: abs(3 - sqrt(2) + 4 + sqrt(2) - 7) < 1e-9
   AddingBox<double> addBox5A(3 - std::sqrt(2)), addBox5B(4 + std::sqrt(2));
   AddingBox<double> sumBox5 = addBox5A + addBox5B;
   REQUIRE(std::abs(sumBox5.getItem() - 7.0) < 1e-9); // use std::abs difference to prove double-type eq

   // bool: true + true = true
   AddingBox<bool> addBox6A(true), addBox6B(true);
   AddingBox<bool> sumBox6 = addBox6A + addBox6B;
   REQUIRE(sumBox6.getItem() == true);
}

// Declaration of ComparableBox non-template derived class
// different than + as non-member, overloading < as a member function
class ComparableBox : public PlainBox<int>
{
public:
   using PlainBox<int>::PlainBox;
   bool operator<(const ComparableBox &box2) // pass by const reference
   {
      return this->getItem() < box2.getItem();
   };
};

TEST_CASE("6. Test ComparableBox", "[ComparableBox]")
{
   ComparableBox box1(3), box2(4);
   REQUIRE(box1 < box2);
   REQUIRE(box1.operator<(box2));

   // REQUIRE(box2 > box1); // TODO: explain Why this line would not compile?
}