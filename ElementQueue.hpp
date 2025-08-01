#ifndef ELEMENTQUEUE_HPP
#define ELEMENTQUEUE_HPP

#include "RoomElements.hpp"
#include<queue>
using namespace std;

class ElementQueue
{
    private:
    queue<RoomElements*> elements;

    public:
    void enqueue(RoomElements* element);
    RoomElements* dequeue();
    bool isEmpty() const;
    ~ElementQueue();
};

#endif