#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "PlayerInventory.hpp"
#include<curses.h>

class Player
{
    private:
    int health;

    public:
    PlayerInventory inventory;
    Player();
    int getHealth() const;
    void setHealth(int health);
    void displayPlayerHealth() const;
};

#endif