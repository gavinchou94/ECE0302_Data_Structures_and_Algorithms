/** @file Edge.tpp */

#include "Edge.hpp"

template <typename LabelType>
Edge<LabelType>::Edge() : endVertex(LabelType()), edgeWeight(0)
{
} // end default constructor

template <typename LabelType>
Edge<LabelType>::Edge(const LabelType &end) : endVertex(end), edgeWeight(0)
{
} // end constructor

template <typename LabelType>
Edge<LabelType>::Edge(const LabelType &end, int weight) : endVertex(end), edgeWeight(weight)
{
} // end constructor

template <typename LabelType>
LabelType Edge<LabelType>::getEndVertex() const
{
   return endVertex;
} // end getEndVertex

template <typename LabelType>
int Edge<LabelType>::getWeight() const
{
   return edgeWeight;
} // end getWeight

template <typename LabelType>
void Edge<LabelType>::setWeight(const int newWeight)
{
   edgeWeight = newWeight;
} // end setWeight