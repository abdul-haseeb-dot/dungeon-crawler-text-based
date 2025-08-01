#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "RoomElements.hpp"
#include<string>
using namespace std;

class Enemy : public RoomElements
{
    private:
    string name;
    int attackPower;
    int healthPoints;

    public:
    Enemy(string name, int attackPower, int healthPoints);
    int getAttackPower() const;
    int getHealthPoints() const;
    string getName() const;
    void setHealthPoints(int healthPoints);
};

#endif