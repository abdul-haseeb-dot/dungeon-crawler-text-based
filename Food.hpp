#ifndef FOOD_HPP
#define FOOD_HPP

#include "RoomElements.hpp"
#include<string>
using namespace std;

class Food : public RoomElements
{
    private:
    string name;
    int health;
    int count;

    public:
    Food();
    Food(string name);
    string getName() const;
    int getHealth() const;
    int getCount() const;
    void setCount(int count);
    bool operator==(const Food& other) const;
    bool operator>(const Food& other) const;
};

#endif