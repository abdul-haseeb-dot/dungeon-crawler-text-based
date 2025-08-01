#include "Room.hpp"

Room::Room(int roomNumber) : roomNumber(roomNumber)
{
    roomCompleted=false;
    next=nullptr;
    prev=nullptr;
}

bool Room::getRoomCompleted() const {return roomCompleted;}

int Room::getRoomNumber() const {return roomNumber;}

void Room::setRoomCompleted() {roomCompleted=true;}