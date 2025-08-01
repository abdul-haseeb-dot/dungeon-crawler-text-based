#include "Weapon.hpp"

Weapon::Weapon() {}

Weapon::Weapon(string name) : name(name)
{
    if(name=="Sword")
    {
        uses=3;
        damage=50;
    }
    else if(name=="Mace")
    {
        uses=2;
        damage=45;
    }
    else if(name=="Grenade")
    {
        uses=1;
        damage=120;
    }
    else if(name=="Bow")
    {
        uses=10;
        damage=5;
    }
}

string Weapon::getName() const {return name;}

int Weapon::getUses() const {return uses;}

int Weapon::getDamage() const {return damage;}

void Weapon::setUses(int uses) {this->uses=uses;}

bool Weapon::operator==(const Weapon& other) const {return this->name==other.name;}

bool Weapon::operator<(const Weapon& other) const {return this->damage<other.damage;}