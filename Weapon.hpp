#ifndef WEAPON_HPP
#define WEAPON_HPP

#include "RoomElements.hpp"
#include<string>
using namespace std;

class Weapon : public RoomElements
{
    private:
    string name;
    int uses;
    int damage;

    public:
    Weapon();
    Weapon(string name);
    string getName() const;
    int getUses() const;
    int getDamage() const;
    void setUses(int uses);
    bool operator==(const Weapon& other) const;
    bool operator<(const Weapon& other) const;
};

#endif