/** @file LinkedGraph.tpp */

#include "LinkedGraph.hpp"
#include <queue>

// Initializes an empty graph with no vertices or edges.
template <typename ItemType>
LinkedGraph<ItemType>::LinkedGraph() : numberOfVertices(0), numberOfEdges(0)
{
} // end default constructor

template <typename ItemType>
int LinkedGraph<ItemType>::getNumVertices() const
{
   return numberOfVertices;
} // end getNumVertices

template <typename ItemType>
int LinkedGraph<ItemType>::getNumEdges() const
{
   return numberOfEdges;
} // end getNumEdges

// Adds an undirected edge between start and end with the given weight.
// Returns true if the edge was successfully added, false if:
//   - start == end (self-loops are not allowed)
//   - the edge already exists
//   - the graph is non-empty and neither endpoint exists yet
//     (adding such an edge would violate the connectivity requirement)
template <typename ItemType>
bool LinkedGraph<ItemType>::add(ItemType start, ItemType end, int edgeWeight)
{
   if (start == end)
      return false; // Self-loops are not permitted

   auto startIt = vertices.find(start);
   auto endIt = vertices.find(end);

   // If both vertices already exist, check for a duplicate edge.
   // getEdgeWeight() returns -1 if no edge exists between them.
   if (startIt != vertices.end() && endIt != vertices.end())
   {
      if (startIt->second->getEdgeWeight(end) != -1)
         return false; // Edge already exists; do not add a duplicate
   }

   // Require at least one endpoint to already exist, so the graph stays connected.
   // If neither vertex exists in a non-empty graph, the new edge would form
   // an isolated component, violating the connectivity requirement.
   if (getNumVertices() != 0)
   {
      if (vertices.find(start) == vertices.end() && vertices.find(end) == vertices.end())
         return false;
   }

   // Create vertices if they don't exist, then connect them in both directions
   // (undirected edge = two directed entries, one in each adjacency list).
   auto startVertex = findOrCreateVertex(start);
   auto endVertex = findOrCreateVertex(end);

   startVertex->connect(end, edgeWeight);
   endVertex->connect(start, edgeWeight);

   ++numberOfEdges;
   return true;
} // end add

// Convenience overload for unweighted graphs. Adds an edge with weight 0.
// Note: weight 0 means "edge exists, unweighted" — distinct from -1 ("no edge").
template <typename ItemType>
bool LinkedGraph<ItemType>::add(ItemType start, ItemType end)
{
   return add(start, end, 0);
} // end add

// Removes the undirected edge between start and end.
// If either vertex becomes isolated after removal (no remaining neighbors),
// it is deleted from the graph to preserve the connectivity invariant.
// Returns true if the edge was found and fully removed, false otherwise.
template <typename ItemType>
bool LinkedGraph<ItemType>::remove(ItemType start, ItemType end)
{
   if (start == end)
      return false; // No self-loops exist to remove

   if (vertices.find(start) == vertices.end() || vertices.find(end) == vertices.end())
      return false; // One or both vertices do not exist

   auto startVertex = vertices.at(start);
   auto endVertex = vertices.at(end);

   // Disconnect in both directions. In practice, both disconnects must succeed
   // for a well-formed undirected graph — if one fails it indicates internal
   // inconsistency rather than a recoverable error.
   bool successful = startVertex->disconnect(end);
   if (successful)
   {
      successful = endVertex->disconnect(start);
      if (successful)
      {
         --numberOfEdges;

         // Remove any vertex that has become isolated.
         if (startVertex->getNumberOfNeighbors() == 0)
         {
            vertices.erase(start);
            --numberOfVertices;
         }
         if (endVertex->getNumberOfNeighbors() == 0)
         {
            vertices.erase(end);
            --numberOfVertices;
         }
      }
      else
         successful = false;
   }
   else
      successful = false;

   return successful;
} // end remove

// Returns the weight of the edge between start and end,
// or -1 if either vertex does not exist or no edge connects them.
template <typename ItemType>
int LinkedGraph<ItemType>::getEdgeWeight(ItemType start, ItemType end) const
{
   if (vertices.find(start) == vertices.end())
      return -1;

   return vertices.at(start)->getEdgeWeight(end);
} // end getEdgeWeight

// Marks all vertices as unvisited in preparation for a fresh traversal.
// Uses the member iterator currentVertex as its loop variable — this is safe
// because all traversal entry points call unvisitVertices() before starting
// their own iteration.
template <typename ItemType>
void LinkedGraph<ItemType>::unvisitVertices()
{
   currentVertex = vertices.begin();
   while (currentVertex != vertices.end())
   {
      currentVertex->second->unvisit();
      ++currentVertex;
   }
} // end unvisitVertices

// Performs a depth-first traversal starting from startLabel,
// calling visit() on each reachable vertex's label in DFS order.
// Unreachable vertices (if any) are not visited.
template <typename ItemType>
void LinkedGraph<ItemType>::depthFirstTraversal(ItemType startLabel, std::function<void(ItemType &)> visit)
{
   unvisitVertices();
   depthFirstTraversalHelper(vertices.at(startLabel), visit);
} // end depthFirstTraversal

// Performs a breadth-first traversal starting from startLabel,
// calling visit() on each reachable vertex's label in BFS order.
// Unreachable vertices (if any) are not visited.
template <typename ItemType>
void LinkedGraph<ItemType>::breadthFirstTraversal(ItemType startLabel, std::function<void(ItemType &)> visit)
{
   unvisitVertices();
   breadthFirstTraversalHelper(vertices.at(startLabel), visit);
} // end breadthFirstTraversal

// Recursive DFS helper. Visits startVertex, then recursively visits each
// unvisited neighbor in adjacency-list order.
// Relies on stateful neighbor iteration (resetNeighbor / getNextNeighbor)
template <typename ItemType>
void LinkedGraph<ItemType>::depthFirstTraversalHelper(std::shared_ptr<Vertex<ItemType>> startVertex,
                                                      std::function<void(ItemType &)> visit)
{
   startVertex->visit();
   ItemType startLabel = startVertex->getLabel();
   visit(startLabel);

   startVertex->resetNeighbor(); // Reset iterator before looping over neighbors

   for (int index = 1; index <= startVertex->getNumberOfNeighbors(); index++)
   {
      ItemType currentLabel = startVertex->getNextNeighbor();
      if (!(vertices.at(currentLabel)->isVisited()))
         depthFirstTraversalHelper(vertices.at(currentLabel), visit);
   }
} // end depthFirstTraversalHelper

// Iterative BFS helper using an explicit queue.
// Visits startVertex first, then processes neighbors level by level.
//
// resetNeighbor() is called on each neighbor as it is enqueued, not when it
// is dequeued. This is intentional: it prepares the neighbor's iterator for
// when it will later be dequeued and its own neighbors iterated. Calling it
// at enqueue time avoids a second pass over the queue entries later.
template <typename ItemType>
void LinkedGraph<ItemType>::breadthFirstTraversalHelper(std::shared_ptr<Vertex<ItemType>> startVertex,
                                                        std::function<void(ItemType &)> visit)
{
   std::queue<std::shared_ptr<Vertex<ItemType>>> vertexQueue;

   startVertex->visit();
   ItemType startLabel = startVertex->getLabel();
   visit(startLabel);
   startVertex->resetNeighbor();
   vertexQueue.push(startVertex);

   while (!vertexQueue.empty())
   {
      auto nextVertex = vertexQueue.front();
      vertexQueue.pop();

      // Enqueue each unvisited neighbor of nextVertex.
      for (int index = 1; index <= nextVertex->getNumberOfNeighbors(); index++)
      {
         ItemType neighborLabel = nextVertex->getNextNeighbor();
         auto neighbor = vertices.at(neighborLabel);

         if (!neighbor->isVisited())
         {
            neighbor->visit();
            visit(neighborLabel);
            neighbor->resetNeighbor(); // Prepare iterator for when this neighbor is dequeued
            vertexQueue.push(neighbor);
         }
      }
   }
} // end breadthFirstTraversalHelper

// Returns the vertex with the given label if it already exists,
// or creates and registers a new one if it does not.
// Increments numberOfVertices on creation.
template <typename ItemType>
std::shared_ptr<Vertex<ItemType>> LinkedGraph<ItemType>::findOrCreateVertex(const ItemType &vertexLabel)
{
   if (vertices.find(vertexLabel) != vertices.end())
      return vertices.at(vertexLabel);

   // Vertex does not exist yet — create it and register it in the map.
   auto theVertex = std::make_shared<Vertex<ItemType>>(vertexLabel);
   vertices.insert({vertexLabel, theVertex});
   ++numberOfVertices;
   return theVertex;
} // end findOrCreateVertex