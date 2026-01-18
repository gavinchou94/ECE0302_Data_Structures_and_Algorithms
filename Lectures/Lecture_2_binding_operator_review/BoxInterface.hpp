/** @file BoxInterface.hpp */

#ifndef BOX_INTERFACE_
#define BOX_INTERFACE_

template <typename ItemType>
class BoxInterface
{
public:
   virtual void setItem(const ItemType &theItem) = 0;
   virtual ItemType getItem() const = 0;
   virtual ~BoxInterface() {}
};
#endif