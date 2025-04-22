/** @file Vertex.tpp */

#include "Vertex.hpp"

template <class LabelType>
Vertex<LabelType>::Vertex(LabelType label) : vertexLabel(label), visited(false)
{
} // end constructor

template <class LabelType>
LabelType Vertex<LabelType>::getLabel() const
{
   return vertexLabel;
} // end getLabel

template <class LabelType>
void Vertex<LabelType>::visit()
{
   visited = true;
} // end visit

template <class LabelType>
void Vertex<LabelType>::unvisit()
{
   visited = false;
} // end unvisit

template <class LabelType>
bool Vertex<LabelType>::isVisited() const
{
   return visited;
} // end isVisited

template <class LabelType>
bool Vertex<LabelType>::connect(const LabelType &endVertex, const int edgeWeight)
{
   Edge<LabelType> thisEdge(endVertex, edgeWeight);
   return adjacencyList.insert({endVertex, thisEdge}).second;
   // insert is a method in std::map
   // .second indicates whether the insertion was successful
} // end connect

template <class LabelType>
bool Vertex<LabelType>::disconnect(const LabelType &endVertex)
{
   return adjacencyList.erase(endVertex);
} // end disconnect

template <class LabelType>
int Vertex<LabelType>::getEdgeWeight(const LabelType &endVertex) const
{
   int edgeWeight = -1;
   if (adjacencyList.find(endVertex) == adjacencyList.end())
      return edgeWeight; // Edge does not exist
   Edge<LabelType> theEdge = adjacencyList.at(endVertex);
   // at is a method in std::map
   // that returns the value associated with the key
   edgeWeight = theEdge.getWeight();
   return edgeWeight;
} // end getEdgeWeight

template <class LabelType>
int Vertex<LabelType>::getNumberOfNeighbors() const
{
   return adjacencyList.size();
} // end getNumberOfNeighbors

template <class LabelType>
void Vertex<LabelType>::resetNeighbor()
{
   currentNeighbor = adjacencyList.begin();
} // end resetNeighbor

template <class LabelType>
LabelType Vertex<LabelType>::getNextNeighbor()
{
   if (currentNeighbor != adjacencyList.end())
   {
      LabelType thisNeighbor = currentNeighbor->second.getEndVertex();
      ++currentNeighbor;
      return thisNeighbor;
   }
   else
      return this->getLabel(); // Signal end of adjacency list
} // end getNextNeighbor

template <class LabelType>
bool Vertex<LabelType>::operator==(const Vertex<LabelType> &rightHandItem) const
{
   return (vertexLabel == rightHandItem.vertexLabel);
} // end operator==

template <class LabelType>
int Vertex<LabelType>::getNeighborPosition(const LabelType &neighborVertex) const
{
   int position = 0;
   bool foundNeighbor = false;

   for (auto it = adjacencyList.begin(); it != adjacencyList.end(); ++it)
   {
      position++;
      // Check if the label matches the neighbor vertex
      if (it->second.getEndVertex() == neighborVertex)
      {
         foundNeighbor = true;
         break;
      }
   }

   if (!foundNeighbor)
      position = -position;

   return position;
} // end getNeighborPosition
