/** @file GraphSearch.tpp */
#include "GraphSearch.hpp"
#include <queue>
#include <algorithm>

// A*: finds the shortest path from start to goal using the given heuristic.
// Returns an empty vector if no path exists.
template <typename ItemType>
std::vector<ItemType> GraphSearch<ItemType>::AStarSearch(
    const ItemType &start,
    const ItemType &goal,
    typename GraphSearch<ItemType>::Heuristic heuristic)
{
    using PQElement = std::pair<int, ItemType>;                                              // pair a node with its fCost = gCost + heuristic
    std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> openSet; // priority queue, ordered by lowest first
    std::unordered_map<ItemType, int> gCost;                                                 // gCost[node] = cost of cheapest path from start to node
    std::unordered_map<ItemType, ItemType> cameFrom;                                         // cameFrom[node] = node immediately preceding it on cheapest path from start

    gCost[start] = 0;
    openSet.push({heuristic(start, goal), start});

    while (!openSet.empty())
    {
        ItemType current = openSet.top().second;
        openSet.pop();

        if (current == goal)
            return reconstructPath(cameFrom, goal);

        auto neighbors = this->getNeighbors(current);
        for (auto neighborIt = neighbors.begin(); neighborIt != neighbors.end(); ++neighborIt)
        {
            ItemType neighbor = neighborIt->first;
            int cost = neighborIt->second;
            int tentative = gCost[current] + cost;
            if (!gCost.count(neighbor) || tentative < gCost[neighbor])
            // if this path to neighbor is better than any previous one, record it and add to openSet
            {
                cameFrom[neighbor] = current;
                gCost[neighbor] = tentative;
                openSet.push({tentative + heuristic(neighbor, goal), neighbor});
            }
        }
    }
    return {}; // no path found
}

// Walks the cameFrom map back from goal to start, then reverses for correct order.
template <typename ItemType>
std::vector<ItemType> GraphSearch<ItemType>::reconstructPath(
    const std::unordered_map<ItemType, ItemType> &cameFrom,
    ItemType current)
{
    std::vector<ItemType> path;
    while (cameFrom.count(current))
    {
        path.push_back(current);
        current = cameFrom.at(current);
    }
    path.push_back(current); // start node
    std::reverse(path.begin(), path.end());
    return path;
}

template <typename ItemType>
int zeroHeuristic(const ItemType &, const ItemType &)
{
    return 0;
}

// Dijkstra: delegates to A* with a zero heuristic
template <typename ItemType>
std::vector<ItemType> GraphSearch<ItemType>::Dijkstra_from_AStar(
    const ItemType &start,
    const ItemType &goal)
{
    return AStarSearch(start, goal, zeroHeuristic<ItemType>);
}

// Returns shortest distance from start to every reachable vertex
template <typename ItemType>
std::unordered_map<ItemType, int> GraphSearch<ItemType>::dijkstra(const ItemType &start)
{
    using PQElement = std::pair<int, ItemType>;
    std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> openSet;

    std::unordered_map<ItemType, int> dist;
    dist[start] = 0;
    openSet.push({0, start});

    while (!openSet.empty())
    {
        PQElement top = openSet.top();
        int d = top.first;
        ItemType current = top.second;
        openSet.pop();

        if (d > dist[current])
            continue; // stale entry, skip

        auto neighbors = this->getNeighbors(current);
        for (auto neighborIt = neighbors.begin(); neighborIt != neighbors.end(); ++neighborIt)
        {
            ItemType neighbor = neighborIt->first;
            int cost = neighborIt->second;
            int newDist = dist[current] + cost;
            if (!dist.count(neighbor) || newDist < dist[neighbor])
            {
                dist[neighbor] = newDist;
                openSet.push({newDist, neighbor});
            }
        }
    }
    return dist;
} // end dijkstra

/*
Dijkstra(graph, start):
    dist[every node] = ∞
    dist[start] = 0
    push (0, start) into priority queue              // 1 push → O(log V)

    while queue is not empty:
        current = pop minimum from queue             // "find closest neighbor" — V pops total → O(V log V)

        if d > dist[current]:                        // dist[] lookup → O(1) avg
            skip

        for each (neighbor, cost) in neighbors of current:
            newDist = dist[current] + cost
            if newDist < dist[neighbor]:             // dist[] lookup → O(1) avg, E total → O(E)
                dist[neighbor] = newDist             // "update distance"
                push (newDist, neighbor)             // E pushes total → O(E log V)

    return dist

    V pops  × log V  →  O(V log V)
    E pushes × log V  →  O(E log V)
    E dist[] lookups  →  O(E)
    Total: O((V + E) log V)

    Trace for the lecture test graph starting at vertex '0', using the same variables as the code:
    Initial: openSet = [(0,'0')], dist = {'0':0}

    Step  top       current   openSet after step                            dist after step
    1     (0,'0')   '0'       [(4,'4'), (8,'1'), (9,'3')]                  {'0':0, '1':8, '3':9, '4':4}
    2     (4,'4')   '4'       [(5,'2'), (8,'1'), (9,'3')]                  {'0':0, '1':8, '2':5, '3':9, '4':4}
    3     (5,'2')   '2'       [(6,'1'), (8,'1'), (8,'3'), (9,'3')]         {'0':0, '1':6, '2':5, '3':8, '4':4}
    4     (6,'1')   '1'       [(8,'1'), (8,'3'), (9,'3')]                  {'0':0, '1':6, '2':5, '3':8, '4':4}
    5     (8,'3')   '3'       []                                           {'0':0, '1':6, '2':5, '3':8, '4':4}

    Note: stale entries like (8,'1') and (9,'3') are skipped by if (d > dist[current]) continue;
*/