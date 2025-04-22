/** A simple class of edges.
   (Conceptually this is similar to the class "Entry")
 @file Edge.hpp */

#ifndef _EDGE
#define _EDGE

template <class LabelType>
class Edge
{
private:
   LabelType endVertex; // Cannot be changed as doing so changes the edge
   int edgeWeight;

public:
   Edge();
   Edge(const LabelType &end);
   Edge(const LabelType &end, int weight);

   LabelType getEndVertex() const;
   int getWeight() const;
   void setWeight(const int newWeight);
}; // end Edge

#include "Edge.tpp"
#endif
