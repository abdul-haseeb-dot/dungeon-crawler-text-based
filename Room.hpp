#ifndef ROOM_HPP
#define ROOM_HPP

#include "ElementQueue.hpp"

class Room
{
    private:
    int roomNumber;
    bool roomCompleted;

    public:
    ElementQueue roomElements;
    Room* next;
    Room* prev;
    Room(int roomNumber);
    bool getRoomCompleted() const;
    int getRoomNumber() const;
    void setRoomCompleted();
};

#endif