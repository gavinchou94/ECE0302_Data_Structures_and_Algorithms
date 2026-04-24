/** @file LinkedGraph.hpp */

#ifndef _LINKED_GRAPH
#define _LINKED_GRAPH

#include "abstract_graph.hpp"
#include "Vertex.hpp"

// For adjacency list; this choice can vary according to how you want to implement the
// adjacency list, and it can differ from the collection used in the class Vertex.

template <typename ItemType>
class LinkedGraph : public AbstractGraph<ItemType>
{
private:
   int numberOfVertices;
   int numberOfEdges;

   std::map<ItemType, std::shared_ptr<Vertex<ItemType>>> vertices;
      // each vertex has a label and a pointer to the vertex object
      // using shared_ptr to manage memory automatically
   
   typename std::map<ItemType, std::shared_ptr<Vertex<ItemType>>>::iterator currentVertex;

   void unvisitVertices(); // Marks all vertices as unvisited.

   std::shared_ptr<Vertex<ItemType>> findOrCreateVertex(const ItemType &vertexLabel);
       // Finds the vertex with the given label and returns a pointer to it.
       // If such a vertex does not exist, creates it, adds it to the graph, and returns a pointer to it.

   void depthFirstTraversalHelper(std::shared_ptr<Vertex<ItemType>> startVertex, std::function<void(ItemType &)> visit);
   void breadthFirstTraversalHelper(std::shared_ptr<Vertex<ItemType>> startVertex, std::function<void(ItemType &)> visit);

public:
   LinkedGraph();
   int getNumVertices() const;
   int getNumEdges() const;
   bool add(ItemType start, ItemType end);
   bool add(ItemType start, ItemType end, int edgeWeight);

   // For remove to return true all of the following must be true:
   // 1) start and end vertices exist
   // 2) Edge start->end is successfully disconnected
   // 3) Edge end->start is successfully disconnected
   // Then, if those are successful and either start or end no longer
   // has neighbors, the vertex is removed from the graph
   bool remove(ItemType start, ItemType end);

   int getEdgeWeight(ItemType start, ItemType end) const;
   void depthFirstTraversal(ItemType start, std::function<void(ItemType &)> visit);
   void breadthFirstTraversal(ItemType start, std::function<void(ItemType &)> visit);
}; // end GraphInterface

#include "LinkedGraph.tpp"
#endif