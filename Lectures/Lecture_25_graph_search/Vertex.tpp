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

// Marks this vertex as unvisited. Called before a traversal begins
// (via LinkedGraph::unvisitVertices()) to reset traversal state.
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

   // std::map::insert returns {iterator, bool}.
   // .second is true if insertion succeeded (key was new), false if the edge already existed.
   return adjacencyList.insert({endVertex, thisEdge}).second;
} // end connect

template <class LabelType>
bool Vertex<LabelType>::disconnect(const LabelType &endVertex)
{
   // std::map::erase(key) returns the number of elements removed (0 or 1 for a map).
   // Implicitly converts to bool: true if the edge was found and removed.
   return adjacencyList.erase(endVertex);
} // end disconnect

// Returns the weight of the edge from this vertex to endVertex,
// or -1 if no such edge exists.
// Note: -1 is a reserved sentinel meaning "no edge" — valid edge weights
// should never be set to -1 (see Edge::setWeight()).
template <class LabelType>
int Vertex<LabelType>::getEdgeWeight(const LabelType &endVertex) const
{
   if (adjacencyList.find(endVertex) == adjacencyList.end())
      return -1; // Edge does not exist

   return adjacencyList.at(endVertex).getWeight();
} // end getEdgeWeight

template <class LabelType>
int Vertex<LabelType>::getNumberOfNeighbors() const
{
   return adjacencyList.size();
} // end getNumberOfNeighbors

// Resets the internal neighbor iterator to the beginning of the adjacency list.
// Must be called before any loop that uses getNextNeighbor().
template <class LabelType>
void Vertex<LabelType>::resetNeighbor()
{
   currentNeighbor = adjacencyList.begin();
} // end resetNeighbor

// Returns the label of the next neighbor and advances the internal iterator.
// Returns this vertex's own label as a sentinel when the iterator is exhausted.
template <class LabelType>
LabelType Vertex<LabelType>::getNextNeighbor()
{
   if (currentNeighbor != adjacencyList.end())
   {
      // currentNeighbor->first is the neighbor's label;
      // currentNeighbor->second is the Edge connecting to that neighbor.
      LabelType thisNeighbor = currentNeighbor->first;
      ++currentNeighbor;
      return thisNeighbor;
   }
   else
   {
      // Sentinel: iterator is exhausted. Caller should never reach here
      // if the loop is correctly bounded by getNumberOfNeighbors().
      return this->getLabel();
   }
} // end getNextNeighbor

template <class LabelType>
bool Vertex<LabelType>::operator==(const Vertex<LabelType> &rightHandItem) const
{
   return (vertexLabel == rightHandItem.vertexLabel);
} // end operator==