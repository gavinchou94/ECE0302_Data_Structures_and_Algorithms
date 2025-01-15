/** @file ToyBox.hpp */

#ifndef TOY_BOX_
#define TOY_BOX_
#include "PlainBox.hpp"

enum Color {BLACK, RED, BLUE, GREEN, YELLOW, WHITE};

template <typename ItemType>
class ToyBox : public PlainBox<ItemType>
{
private:
   Color boxColor;
public:
   ToyBox();
   ToyBox(const Color& theColor);
   ToyBox(const ItemType& theItem, const Color& theColor);
   Color getColor() const;
};
#include "ToyBox.tpp"
#endif