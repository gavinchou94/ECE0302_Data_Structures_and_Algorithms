#include "priority_queue.hpp"

template <typename T, typename L>
bool PriorityQueue<T, L>::isEmpty() const
{
    return slist.isEmpty();
}

template <typename T, typename L>
void PriorityQueue<T, L>::add(const T &item)
{
    slist.insert(item);
}

template <typename T, typename L>
void PriorityQueue<T, L>::remove()
{
    // priority queue's front is the last item in the sorted list
    slist.removeAt(slist.getLength());
}

template <typename T, typename L>
T PriorityQueue<T, L>::peek()
{
    // priority queue's front is the last item in the sorted list
    return slist.getEntry(slist.getLength());
}