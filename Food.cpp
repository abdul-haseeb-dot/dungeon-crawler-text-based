#include "Food.hpp"

Food::Food() {}

Food::Food(string name) : name(name)
{
    count = 1;
    if(name == "Apple")
        health = 10;
    else if(name == "Peach")
        health = 30;
    else if(name == "Dinner")
        health = 70;
    else if(name == "Potion")
        health = 100;
}

string Food::getName() const {return name;}

int Food::getHealth() const {return health;}

int Food::getCount() const {return count;}

void Food::setCount(int count) {this->count=count;}

bool Food::operator==(const Food& other) const {return this->name==other.name;}

bool Food::operator>(const Food& other) const {return this->health>other.health;}