/** @file LinkedGraph.hpp */

#ifndef _LINKED_GRAPH
#define _LINKED_GRAPH

#include "abstract_graph.hpp"
#include "Vertex.hpp"

// For adjacency list; this choice can vary according to how you want to implement the
// adjacency list, and it can differ from the collection used in the class Vertex.

template <class ItemType>
class LinkedGraph : public AbstractGraph<ItemType>
{
private:
   int numberOfVertices;
   int numberOfEdges;

   std::map<ItemType, std::shared_ptr<Vertex<ItemType>>> vertices;
   typename std::map<ItemType, std::shared_ptr<Vertex<ItemType>>>::iterator currentVertex;

   // Marks all vertices as unvisited.
   void unvisitVertices();
   std::shared_ptr<Vertex<ItemType>> findOrCreateVertex(const ItemType &vertexLabel);

   void depthFirstTraversalHelper(std::shared_ptr<Vertex<ItemType>> startVertex, void visit(ItemType &));
   void breadthFirstTraversalHelper(std::shared_ptr<Vertex<ItemType>> startVertex, void visit(ItemType &));

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
   void depthFirstTraversal(ItemType start, void visit(ItemType &));
   void breadthFirstTraversal(ItemType start, void visit(ItemType &));
}; // end GraphInterface

#include "LinkedGraph.tpp"
#endif