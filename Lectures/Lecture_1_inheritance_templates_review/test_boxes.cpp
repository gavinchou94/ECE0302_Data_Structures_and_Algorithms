/** @file test_boxes.cpp
 * @author Frank M. Carrano, Tim Henry
 * @copyright 2016 Pearson Education
 * @version 3.0, modified in 2026 by G. Zhou for ECE0302
 */

#define CATCH_CONFIG_MAIN
#include "BoxInterface.hpp"
#include "PlainBox.hpp"
#include "ToyBox.hpp"
#include "MagicBox.hpp"

#include "catch.hpp"

TEST_CASE("1. Test PlainBox templates with different data types", "[PlainBox]")
{

   PlainBox<double> numberBox;    // A box to hold a double
   PlainBox<std::string> nameBox; // A box to hold a string object

   double health = 6.5;
   numberBox.setItem(health);

   std::string secretName = "Rumpelstiltskin";
   nameBox.setItem(secretName);

   REQUIRE(numberBox.getItem() == 6.5);
   REQUIRE(nameBox.getItem() == "Rumpelstiltskin");
}

TEST_CASE("2. Test ToyBox with parameterized constructor and new method", "[ToyBox]")
{

   std::string favoriteToy = "Jack-in-the-Box";
   ToyBox<std::string> myToyCase(favoriteToy, RED);
   REQUIRE(myToyCase.getColor() == RED); // test new method getColor()

   std::string oldToy = myToyCase.getItem(); // oldToy is a Jack-in-the-Box
   REQUIRE(oldToy == "Jack-in-the-Box");

   favoriteToy = "Spinning Top";
   myToyCase.setItem(favoriteToy); // inherit base class method, myToyCase now holds a Spinning Top
   REQUIRE(myToyCase.getItem() == "Spinning Top");

   REQUIRE(myToyCase.getColor() == RED); // base class method does not modify derived class member - boxcolor
}

TEST_CASE("3. Test MagicBox", "[MagicBox]")
{
   PlainBox<std::string> *magicCard = new MagicBox<std::string>("Jack of Diamonds");
   REQUIRE(magicCard->getItem() == "Jack of Diamonds");

   magicCard->setItem("Joker");
   REQUIRE(false); // TODO: edit the REQUIRE statement to test the item stored,
                   // recall that MagicBox would only hold the first item
}

// !!! Not a good practice to declare classes in testing file, just for exercise purposes

// Declare a new base class PlainBox2, only remove one keyword from PlainBox.hpp
// but now it includes the implementation
template <typename ItemType>
class PlainBox2
{
private:
   ItemType item;

public:
   PlainBox2() {};
   PlainBox2(const ItemType &theItem) : item(theItem) {};
   void setItem(const ItemType &theItem) { item = theItem; }; // notice the difference here from PlainBox.hpp
   ItemType getItem() const { return item; };
};

// Derive a class called MagicBox2, only remove one keyword from MagicBox.hpp
// but now it includes the implementation
template <typename ItemType>
class MagicBox2 : public PlainBox2<ItemType>
{
private:
   bool firstItemStored;

public:
   MagicBox2() : firstItemStored(false) {};
   MagicBox2(const ItemType &theItem) : firstItemStored(false) { setItem(theItem); };
   void setItem(const ItemType &theItem)
   {
      if (!firstItemStored)
      {
         PlainBox2<ItemType>::setItem(theItem);
         firstItemStored = true;
      }
   };
};

TEST_CASE("4. Test MagicBox2", "[MagicBox2]")
{
   PlainBox2<std::string> *magicCard2 = new MagicBox2<std::string>("Jack of Diamonds");
   REQUIRE(magicCard2->getItem() == "Jack of Diamonds");

   magicCard2->setItem("Joker");
   REQUIRE(false); // TODO: edit the REQUIRE statement to test the item stored,
                   // recall that MagicBox2 is supposed to only hold the first item with proper implementation
}

TEST_CASE("5. Test BoxInterface", "[BoxInterface]")
{
   // BoxInterface<int> boxOfIntegers;    // TODO: explain why this line of code would not compile?

   BoxInterface<char> *generalBox[3];

   // TODO: which single line would you modify in PlainBox.hpp to make the following code block compile?
   //       think about the hierarchy of UML of all these classes?

   // generalBox[0] = new PlainBox<char>('P');
   // generalBox[1] = new ToyBox<char>('T', WHITE);
   // generalBox[2] = new MagicBox<char>('M');
   // REQUIRE(generalBox[0]->getItem()=='P');
   // REQUIRE(generalBox[1]->getItem()=='T');
   // REQUIRE(generalBox[2]->getItem()=='M');
}