/** @file Edge.tpp */

#include "Edge.hpp"

template <class LabelType>
Edge<LabelType>::Edge() : endVertex(LabelType()), edgeWeight(0)
{
} // end default constructor

template <class LabelType>
Edge<LabelType>::Edge(const LabelType &end) : endVertex(end), edgeWeight(0)
{
} // end constructor

template <class LabelType>
Edge<LabelType>::Edge(const LabelType &end, int weight) : endVertex(end), edgeWeight(weight)
{
} // end constructor

template <class LabelType>
LabelType Edge<LabelType>::getEndVertex() const
{
   return endVertex;
} // end getEndVertex

template <class LabelType>
int Edge<LabelType>::getWeight() const
{
   return edgeWeight;
} // end getWeight

template <class LabelType>
void Edge<LabelType>::setWeight(const int newWeight)
{
   edgeWeight = newWeight;
} // end setWeight
