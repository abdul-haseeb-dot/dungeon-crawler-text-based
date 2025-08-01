#include "PlayerInventory.hpp"
#include<algorithm>
using namespace std;

PlayerInventory::PlayerInventory()
{
    keys[0]=true; //Starting Room Should be Unlocked
    keys[1]=keys[2]=false;
}

void PlayerInventory::addWeapon(const Weapon W)
{
    bool alreadyExists=false;
    int index;
    for(int i=0;i<=weapons.getSize();i++)
    {
        if(weapons.getArray()[i]==W) //If the weapon already exists in the inventory, do not add it again. Add its uses instead.
        {
            alreadyExists=true;
            index=i;
            break;
        }
    }
    if(alreadyExists)
    {
        weapons.getArray()[index].setUses(weapons.getArray()[index].getUses()+W.getUses());
    }
    else
    {
        weapons.addItem(W);
        sortWeapons();
    }
}

void PlayerInventory::addFood(const Food F)
{
    bool alreadyExists=false;
    int index;
    for(int i=0;i<=foods.getSize();i++)
    {
        if(foods.getArray()[i]==F) //If the food already exists in the inventory, do not add it again. Add its count instead.
        {
            alreadyExists=true;
            index=i;
            break;
        }
    }
    if(alreadyExists)
    {
        foods.getArray()[index].setCount(foods.getArray()[index].getCount()+F.getCount());
    }
    else
    {
        foods.addItem(F);
        sortFoods();
    }
}

void PlayerInventory::removeWeapon()
{
    for(int i=0;i<=weapons.getSize();i++)
    {
        if(weapons.getArray()[i].getUses()==0)
        {
            weapons.removeItem(i);
            break;
        }
    }
}

void PlayerInventory::removeFood()
{
    for(int i=0;i<=foods.getSize();i++)
    {
        if(foods.getArray()[i].getCount()==0)
        {
            foods.removeItem(i);
            break;
        }
    }
}

bool PlayerInventory::hasKey(int index) const {return keys[index];}

void PlayerInventory::unlockKey(int index) {keys[index]=true;}

void PlayerInventory::sortWeapons()
{
    //Uses insertion sort to make sure the weapons are sorted in ascending order of damage in the inventory
    int n=weapons.getSize()+1;
    for(int i=0;i<n;i++)
    {
        for(int j=i;j>0;j--)
        {
            if(weapons.getArray()[j]<weapons.getArray()[j-1])
            {
                swap(weapons.getArray()[j],weapons.getArray()[j-1]);
            }
            else
            {
                break;
            }
        }
    }
}

void PlayerInventory::sortFoods()
{
    //Uses shell sort to make sure the foods are sorted in ascending order of health in the inventory
    int n=foods.getSize()+1;
    for(int gap=n/2;gap>0;gap/=2)
    {
        for(int i=gap;i<n;i++)
        {
            Food temp=foods.getArray()[i];
            int j=i;
            for(;j>=gap&&foods.getArray()[j-gap]>temp;j-=gap)
            {
                foods.getArray()[j]=foods.getArray()[j-gap];
            }
            foods.getArray()[j]=temp;
        }
    }
}