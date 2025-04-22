/** @file LinkedGraph.tpp */

#include "LinkedGraph.hpp"
#include <queue>

template <class ItemType>
LinkedGraph<ItemType>::LinkedGraph() : numberOfVertices(0), numberOfEdges(0)
{
} // end default constructor

template <class ItemType>
int LinkedGraph<ItemType>::getNumVertices() const
{
   return numberOfVertices;
} // end getNumVertices

template <class ItemType>
int LinkedGraph<ItemType>::getNumEdges() const
{
   return numberOfEdges;
} // end getNumEdges

template <class ItemType>
bool LinkedGraph<ItemType>::add(ItemType start, ItemType end)
{
   // Return false if start and end are the same
   if (start == end)
   {
      return false;
   }
   auto startIt = vertices.find(start);
   auto endIt = vertices.find(end);
   if (startIt != vertices.end() && endIt != vertices.end())
   {
      if (startIt->second->getEdgeWeight(end) != -1)
         return false; // Edge already exists, do not add duplicate
   }

   // not creating a disconnected graph
   if (getNumVertices() != 0)
   {
      if (vertices.find(start) == vertices.end() && vertices.find(end) == vertices.end())
      {
         return false; // Both vertices do not exist, creating a disconnected graph
      }
   }

   int edgeWeight = 0; // Default weight for unweighted graph
   auto startVertex = findOrCreateVertex(start);
   auto endVertex = findOrCreateVertex(end);

   startVertex->connect(end, edgeWeight);
   endVertex->connect(start, edgeWeight);

   ++numberOfEdges;

   return true;
} // end add

template <class ItemType>
bool LinkedGraph<ItemType>::add(ItemType start, ItemType end, int edgeWeight)
{
   // Check if start and end are the same
   if (start == end)
   {
      return false; // Cannot add an edge to itself
   }

   // Check if the edge already exists
   if (vertices.find(start) != vertices.end() && vertices.at(start)->getEdgeWeight(end) != -1)
   {
      return false; // Edge already exists, do not add duplicate
   }

   // not creating a disconnected graph
   if (getNumVertices() != 0)
   {
      if (vertices.find(start) == vertices.end() && vertices.find(end) == vertices.end())
      {
         return false; // Both vertices do not exist, creating a disconnected graph
      }
   }

   auto startVertex = findOrCreateVertex(start);
   auto endVertex = findOrCreateVertex(end);

   startVertex->connect(end, edgeWeight);
   endVertex->connect(start, edgeWeight);

   numberOfEdges++;

   return true;
} // end add

template <class ItemType>
bool LinkedGraph<ItemType>::remove(ItemType start, ItemType end)
{
   bool successful = false;
   if (start == end)
   {
      return false; // Cannot remove an edge to itself
   }
   // Check if the edge exists
   if (vertices.find(start) == vertices.end() || vertices.find(end) == vertices.end())
   {
      return false; // One or both vertices do not exist
   }

   // not creating a disconnected graph
   if (getNumVertices() != 0)
   {
      if (vertices.find(start) == vertices.end() && vertices.find(end) == vertices.end())
      {

         return false; // Both vertices do not exist, creating a disconnected graph
      }
   }

   auto startVertex = vertices.at(start);
   auto endVertex = vertices.at(end);

   successful = startVertex->disconnect(end);
   if (successful)
   {
      successful = endVertex->disconnect(start);
      if (successful)
      {
         numberOfEdges--;

         // If either vertex no longer has a neighbor, remove it
         if (startVertex->getNumberOfNeighbors() == 0)
         {
            vertices.erase(start);
            numberOfVertices--;
         }
         if (endVertex->getNumberOfNeighbors() == 0)
         {
            vertices.erase(end);
            numberOfVertices--;
         }
      }
      else
         successful = false; // Failed disconnect from endVertex
   }
   else
      successful = false; // Failed disconnect from startVertex

   return successful;
} // end remove

template <class ItemType>
int LinkedGraph<ItemType>::getEdgeWeight(ItemType start, ItemType end) const
{
   int weight = -1;
   if (vertices.find(start) != vertices.end())
   {
      auto startVertex = vertices.at(start);
      weight = startVertex->getEdgeWeight(end);
   } // end if

   return weight;
} // end getEdgeWeight

// Mark all vertices as unvisited
template <class ItemType>
void LinkedGraph<ItemType>::unvisitVertices()
{
   currentVertex = vertices.begin();
   while (currentVertex != vertices.end())
   {
      auto loopVertex = currentVertex->second;
      loopVertex->unvisit();
      ++currentVertex;
   } // end while
} // end unvisitVertices

template <class ItemType>
void LinkedGraph<ItemType>::depthFirstTraversal(ItemType startLabel, void visit(ItemType &))
{
   // Mark all vertices as unvisited
   unvisitVertices();

   auto startVertex = vertices.at(startLabel);
   depthFirstTraversalHelper(startVertex, visit);
} // end depthFirstTraversal

template <class ItemType>
void LinkedGraph<ItemType>::breadthFirstTraversal(ItemType startLabel,
                                                  void visit(ItemType &))
{
   // Mark all vertices as unvisited
   unvisitVertices();

   auto startVertex = vertices.at(startLabel);
   breadthFirstTraversalHelper(startVertex, visit);
} // end breadthFirstTraversal

template <class ItemType>
void LinkedGraph<ItemType>::depthFirstTraversalHelper(std::shared_ptr<Vertex<ItemType>> startVertex, void visit(ItemType &))
{
   startVertex->visit(); // Mark as visited
   ItemType startLabel = startVertex->getLabel();
   visit(startLabel);

   startVertex->resetNeighbor(); // Reset reference for adjacency list

   for (int index = 1; index <= startVertex->getNumberOfNeighbors(); index++)
   {
      ItemType currentLabel = startVertex->getNextNeighbor();
      if (!((vertices.at(currentLabel))->isVisited()))
         depthFirstTraversalHelper(vertices.at(currentLabel), visit);
   } // end for
} // end depthFirstTraversalHelper

template <class ItemType>
void LinkedGraph<ItemType>::breadthFirstTraversalHelper(std::shared_ptr<Vertex<ItemType>> startVertex, void visit(ItemType &))
{
   std::queue<std::shared_ptr<Vertex<ItemType>>> vertexQueue;
   ItemType startLabel = startVertex->getLabel();
   //   cout << "Enqueue and visit " << startLabel << endl;
   vertexQueue.push(startVertex);
   startVertex->visit(); // Mark as visited
   visit(startLabel);
   startVertex->resetNeighbor(); // Reset reference for adjacency list

   while (!vertexQueue.empty())
   {
      // Remove vertex from queue
      auto nextVertex = vertexQueue.front();
      vertexQueue.pop();
      ItemType nextLabel = nextVertex->getLabel();
      //      cout << "Dequeue " << nextLabel << endl;
      //      cout << "Consider " << nextLabel << "'s " << nextVertex->getNumberOfNeighbors() << " neighbors." << endl;

      // Add neighbors of visited vertex to queue
      for (int index = 1; index <= nextVertex->getNumberOfNeighbors(); index++)
      {
         ItemType neighborLabel = nextVertex->getNextNeighbor();
         //         cout << "Neighbor " << neighborLabel;
         auto neighbor = vertices.at(neighborLabel);
         if (!neighbor->isVisited())
         {
            //            cout << " is not visited; enqueue and visit it." << endl;
            vertexQueue.push(neighbor);
            neighbor->visit(); // Mark as visited
            visit(neighborLabel);
            neighbor->resetNeighbor(); // Reset reference for adjacency list
         }
         //         else
         //            cout << " was visited already; ignore it." << endl;
      } // end for
   } // end while
} // end breadthFirstTraversalHelper

template <class ItemType>
std::shared_ptr<Vertex<ItemType>> LinkedGraph<ItemType>::findOrCreateVertex(const ItemType &vertexLabel)
{
   std::shared_ptr<Vertex<ItemType>> theVertex = nullptr;

   if (vertices.find(vertexLabel) != vertices.end())
   {
      theVertex = vertices.at(vertexLabel);
   }
   else
   {
      theVertex = std::make_shared<Vertex<ItemType>>(vertexLabel);
      vertices.insert({vertexLabel, theVertex});
      numberOfVertices++;
   } // end if

   return theVertex;
} // end findOrCreateVertex