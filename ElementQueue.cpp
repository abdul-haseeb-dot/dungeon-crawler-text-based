#include "ElementQueue.hpp"

void ElementQueue::enqueue(RoomElements* element)
{
    elements.push(element);
}

RoomElements* ElementQueue::dequeue()
{
    if (elements.empty())
        return nullptr;
    RoomElements* element=elements.front();
    elements.pop();
    return element;
}

bool ElementQueue::isEmpty() const {return elements.empty();}

ElementQueue::~ElementQueue()
{
    while (!elements.empty())
    {
        delete elements.front();
        elements.pop();
    }
}