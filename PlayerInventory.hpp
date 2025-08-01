#ifndef PLAYERINVENTORY_HPP
#define PLAYERINVENTORY_HPP

#include "Inventory.hpp"
#include "Weapon.hpp"
#include "Food.hpp"

class PlayerInventory
{
    private:
    bool keys[3];

    public:
    Inventory<Weapon> weapons;
    Inventory<Food> foods;

    PlayerInventory();
    void addWeapon(const Weapon W);
    void addFood(const Food F);
    void removeWeapon();
    void removeFood();
    bool hasKey(int index) const;
    void unlockKey(int index);
    void sortWeapons();
    void sortFoods();
};

#endif