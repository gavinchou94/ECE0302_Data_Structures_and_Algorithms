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
   std::map<ItemType, int> getNeighbors(ItemType vertexLabel) const;

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

// Edge class visualization:
// ('L', 15)         --15--> 'L'  : there is an edge ending at 'L' with weight 15
// ('M', 10)         --10--> 'M'  : there is an edge ending at 'M' with weight 10
// ('T', 42)         --42--> 'T'  : there is an edge ending at 'T' with weight 42

// Vertex class visualization:
// ('M', true, adjList={('L', --15--> 'L')}, curr='L')

// There is a vertex with label 'M', it is visited,
// it has one neighbor 'L' with an edge of weight 15, and the current neighbor is 'L'.

// ('L', false, adjList={('M', --15--> 'M'), ('T', --42--> 'T')}, curr='T')

// There is a vertex with label 'L', it is not visited,
// it has two neighbors 'M' and 'T' with edges of weights 15 and 42 respectively,
// and the current neighbor is 'T'.

// ('T', false, adjList={('L', --42--> 'L')}, curr='L')

// Graph class visualization:
// numVertices=3, numEdges=2, vertices_map={
// 'L' mapped to ['L'] vertex object,
// 'M' mapped to ['M'] vertex object,
// 'T' mapped to ['T'] vertex object
// }
// currentVertex='M'
//    'M' --15-- 'L'
//                |
//                |
//               42
//                |
//                |
//               'T'