#ifndef _ABSTRACT_GRAPH_H_
#define _ABSTRACT_GRAPH_H_

#include <cstdlib>

template <typename ItemType>
class AbstractGraph
{
public:
  // virtual destructor to ensure overriding
  virtual ~AbstractGraph() {};

  /** Gets the number of vertices in this graph.
    @pre None.
    @return The number of vertices in the graph. */
  virtual int getNumVertices() const = 0;

  /** Gets the number of edges in this graph.
   @pre None.
   @return The number of edges in the graph. */
  virtual int getNumEdges() const = 0;

  /** Creates an undirected edge in this graph between two vertices
       that have the given labels. If such vertices do not exist, creates
       them and adds them to the graph before creating the edge.
       If such an edge(undirected) already exists, does nothing and returns false.
       If start and end are the same, does nothing and returns false.
       If the addition makes the graph disconnected, does nothing and returns false.
    @param start  A label for the first vertex.
    @param end  A label for the second vertex.
    @return  True if the edge is created, or false otherwise. */
  virtual bool add(ItemType start, ItemType end) = 0;

  /** Removes an edge from this graph. If a vertex has no other edges,
       it is removed from the graph since this is a connected graph.
       If such an edge(undirected) does not exist, does nothing and returns false.
       If start and end are the same, does nothing and returns false.
    @pre  None.
    @param start  A label for the first vertex.
    @param end  A label for the second vertex.
    @return  True if the edge is removed, or false otherwise. */
  virtual bool remove(ItemType start, ItemType end) = 0;

  /** Performs a depth-first search of this graph beginning at the given
       vertex and calls a given function once for each vertex visited.
    @param start  A label for the first vertex.
    @param visit  A client-defined function (e.g., print) that performs an operation on
       or with each visited vertex. */
  virtual void depthFirstTraversal(ItemType start, void visit(ItemType &)) = 0;

  /** Performs a breadth-first search of this graph beginning at the given
      vertex and calls a given function once for each vertex visited.
   @param start  A label for the first vertex.
   @param visit  A client-defined function (e.g. print) that performs an operation on
      or with each visited vertex. */
  virtual void breadthFirstTraversal(ItemType start, void visit(ItemType &)) = 0;
};

#endif
