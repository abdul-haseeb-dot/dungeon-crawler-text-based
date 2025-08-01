#include "Dungeon.hpp"
#include<iostream>
#include<cstdlib>
#include<string>
#include<algorithm>
using namespace std;

Dungeon::Dungeon()
{
    Room* room1=new Room(1);
    Room* room2=new Room(2);
    Room* room3=new Room(3);

    room1->next=room2;
    room2->prev=room1;
    room2->next=room3;
    room3->prev=room2;
    start=room1;
    current=room1;

    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    
    menuWin=newwin(3, cols, 0, 0);
    inventoryWin=newwin(rows-6, cols/3, 3, 0);
    gameWin=newwin(rows-6, cols*2/3, 3, cols/3);
    statusWin=newwin(3, cols, rows-3, 0);
    
    box(menuWin, 0, 0);
    box(inventoryWin, 0, 0);
    box(gameWin, 0, 0);
    mvwprintw(gameWin, 0, 2, "Game");
    box(statusWin, 0, 0);
    
    updateInventory();
    updateStatus();
    updateMenu();
}

Dungeon::~Dungeon()
{
    delwin(menuWin);
    delwin(inventoryWin);
    delwin(gameWin);
    delwin(statusWin);
    Room* temp;
    while(start!=nullptr)
    {
        temp=start;
        start=start->next;
        delete temp;
    }
}

Room* Dungeon::getStart() const {return start;}

void Dungeon::updateMenu()
{
    werase(menuWin);
    box(menuWin, 0, 0);
    string title="Dungeon Crawler Game";
    int winRows, winCols;
    getmaxyx(menuWin, winRows, winCols);
    int x=(winCols-title.length())/2;
    wattron(menuWin, COLOR_PAIR(8) | A_BOLD);
    mvwprintw(menuWin, 1, x, title.c_str());
    wattroff(menuWin, COLOR_PAIR(8) | A_BOLD);
    wrefresh(menuWin);
}

void Dungeon::updateInventory()
{
    werase(inventoryWin);
    wattron(inventoryWin, COLOR_PAIR(1));
    box(inventoryWin, 0, 0);
    mvwprintw(inventoryWin, 0, 2, "Inventory");
    wattroff(inventoryWin, COLOR_PAIR(1));
    wmove(inventoryWin, 1, 1);

    int row=1;
    
    wattron(inventoryWin, COLOR_PAIR(3));
    mvwprintw(inventoryWin, row++, 2, "Weapons:");
    wattroff(inventoryWin, COLOR_PAIR(3));
    if(player.inventory.weapons.getSize()==-1)
    {
        wattron(inventoryWin, COLOR_PAIR(6));
        mvwprintw(inventoryWin, row++, 4, "Empty");
        row++;
        wattroff(inventoryWin, COLOR_PAIR(6));
    }
    else
    {
        for(int i=0;i<=player.inventory.weapons.getSize();i++)
        {
            wattron(inventoryWin, COLOR_PAIR(3));
            mvwprintw(inventoryWin, row++, 4, "%d. %s (Damage: %d, Uses: %d)", i+1, player.inventory.weapons.getArray()[i].getName().c_str(), player.inventory.weapons.getArray()[i].getDamage(), player.inventory.weapons.getArray()[i].getUses());
            wattroff(inventoryWin, COLOR_PAIR(3));
        }
    }
    
    row++;
    wattron(inventoryWin, COLOR_PAIR(4));
    mvwprintw(inventoryWin,row++, 2, "Foods:");
    wattroff(inventoryWin, COLOR_PAIR(4));
    if(player.inventory.foods.getSize() == -1)
    {
        wattron(inventoryWin, COLOR_PAIR(6));
        mvwprintw(inventoryWin, row++, 4, "Empty");
        wattroff(inventoryWin, COLOR_PAIR(6));
    }
    else
    {
        for(int i=0;i<=player.inventory.foods.getSize();i++)
        {
            wattron(inventoryWin, COLOR_PAIR(4));
            mvwprintw(inventoryWin, row++, 4, "%d. %s (Health: %d, Count: %d)", i+1, player.inventory.foods.getArray()[i].getName().c_str(), player.inventory.foods.getArray()[i].getHealth(), player.inventory.foods.getArray()[i].getCount());
            wattroff(inventoryWin, COLOR_PAIR(4));
        }
    }
    
    row++;
    wattron(inventoryWin, COLOR_PAIR(5));
    mvwprintw(inventoryWin, row++, 2, "Keys:");
    wattroff(inventoryWin, COLOR_PAIR(5));
    for(int i=0;i<3;i++)
    {
        wattron(inventoryWin, COLOR_PAIR(player.inventory.hasKey(i) ? 5 : 6));
        mvwprintw(inventoryWin, row++, 4, "Key %d: %s", i+1, player.inventory.hasKey(i) ? "Unlocked":"Locked");
        wattron(inventoryWin, COLOR_PAIR(player.inventory.hasKey(i) ? 5 : 6));
    }
    
    wrefresh(inventoryWin);
}

void Dungeon::updateStatus()
{
    werase(statusWin);
    box(statusWin, 0, 0);
    mvwprintw(statusWin, 0, 2, "Status Bar");

    int health=player.getHealth();
    int filled=health/5;
    int toalBars=20;

    string barStr="";
    for(int i=1;i<=filled;i++)
        barStr+="+";
    for(int i=filled+1;i<=toalBars;i++)
        barStr+="-";

    int color=(health>50) ? 7 : (health > 20 ? 8 : 9);
    string statusText="Room: "+to_string(current->getRoomNumber())+" | Health: "+to_string(health)+"/100 "+barStr;
    int maxY, maxX;
    getmaxyx(statusWin, maxY, maxX);
    int x=(maxX-statusText.length())/2;

    wattron(statusWin, COLOR_PAIR(color));
    mvwprintw(statusWin, 1, x, statusText.c_str());
    wattroff(statusWin, COLOR_PAIR(color));
    wrefresh(statusWin);
}

void Dungeon::fightEnemy(Enemy enemy)
{
    werase(gameWin);
    box(gameWin, 0, 0);
    mvwprintw(gameWin, 0, 2, "Game");
    int line=1;
    wattron(gameWin, COLOR_PAIR(10));
    mvwprintw(gameWin, line++, 2, "An Enemy appears!");
    wattroff(gameWin, COLOR_PAIR(10));
    wattron(gameWin, COLOR_PAIR(2));
    mvwprintw(gameWin, line++, 2, "Name: %s | Attack Power: %d | Health Points: %d", enemy.getName().c_str(), enemy.getAttackPower(), enemy.getHealthPoints());
    wattroff(gameWin, COLOR_PAIR(2));
    
    line++;
    wattron(gameWin, COLOR_PAIR(1));
    mvwprintw(gameWin, line++, 2, "Player health: ");
    wattroff(gameWin, COLOR_PAIR(1));
    wattron(gameWin, COLOR_PAIR(player.getHealth() > 50 ? 7 : (player.getHealth() > 20 ? 8 : 9)));
    wprintw(gameWin, "%d", player.getHealth());
    wattroff(gameWin, COLOR_PAIR(player.getHealth() > 50 ? 7 : (player.getHealth() > 20 ? 8 : 9)));
    wattron(gameWin, COLOR_PAIR(2));
    mvwprintw(gameWin, line++, 2, "Enemy has %d health", enemy.getHealthPoints());
    wattroff(gameWin, COLOR_PAIR(2));
    
    line++;
    string heading="=== COMBAT STARTED ===";
    int maxY, maxX;
    getmaxyx(gameWin, maxY, maxX);
    int x=(maxX-heading.length())/2;
    wattron(gameWin, COLOR_PAIR(10));
    mvwprintw(gameWin, line++, x, heading.c_str());
    wattroff(gameWin, COLOR_PAIR(10));
    line++;
    wrefresh(gameWin);

    bool combatEnded=false;
    bool isEnemyTurn=rand()%2;

    while(!combatEnded)
    {
        if(isEnemyTurn)
        {
            wattron(gameWin, COLOR_PAIR(2));
            mvwprintw(gameWin, line++, 2, "Enemy's turn!");
            wattroff(gameWin, COLOR_PAIR(2));
            int damage=enemy.getAttackPower();
            player.setHealth(player.getHealth()-damage);
            
            wattron(gameWin, COLOR_PAIR(9));
            mvwprintw(gameWin, line++, 2, "Enemy attacks for %d damage!", damage);
            wattroff(gameWin, COLOR_PAIR(9));
            player.setHealth(max(player.getHealth(), 0));
            wattron(gameWin, COLOR_PAIR(1));
            mvwprintw(gameWin, line++, 2, "Your health: ");
            wattroff(gameWin, COLOR_PAIR(1));
            wattron(gameWin, COLOR_PAIR(player.getHealth() > 50 ? 7 : (player.getHealth() > 20 ? 8 : 9)));
            wprintw(gameWin, "%d", player.getHealth());
            wattroff(gameWin, COLOR_PAIR(player.getHealth() > 50 ? 7 : (player.getHealth() > 20 ? 8 : 9)));
            wrefresh(gameWin);
            updateStatus();
            
            if (player.getHealth()==0)
            {
                throw runtime_error("You have been defeated by the enemy!");
            }
        }
        else
        {
            wattron(gameWin, COLOR_PAIR(1));
            mvwprintw(gameWin, line++, 2, "Your turn!");
            wattroff(gameWin, COLOR_PAIR(1));
            if(player.inventory.weapons.getSize()==-1)
            {
                throw runtime_error("You don't have any weapons! The Enemy kills you! You have been defeated!");
            }
            wattron(gameWin, COLOR_PAIR(1));
            mvwprintw(gameWin, line++, 2, "Choose a weapon (1-%d): ", player.inventory.weapons.getSize()+1);
            wattroff(gameWin, COLOR_PAIR(1));
            wrefresh(gameWin);
            int choice;
            wscanw(gameWin, "%d", &choice);
            box(gameWin, 0, 0);
            wrefresh(gameWin);
            if(choice<1 || choice>player.inventory.weapons.getSize()+1)
            {
                wattron(gameWin, COLOR_PAIR(8));
                mvwprintw(gameWin, line++, 2, "Invalid choice. You fumble and miss your turn!");
                wattroff(gameWin, COLOR_PAIR(8));
                wrefresh(gameWin);
                isEnemyTurn=!isEnemyTurn;
                continue;
            }
            Weapon selectedWeapon=player.inventory.weapons.getArray()[choice-1];
            int damage=selectedWeapon.getDamage();
            enemy.setHealthPoints(enemy.getHealthPoints()-damage);
            if(enemy.getHealthPoints()<0)
            {
                enemy.setHealthPoints(0);
            }
            wattron(gameWin, COLOR_PAIR(7));
            mvwprintw(gameWin, line++, 2, "You attack with %s for %d damage!", selectedWeapon.getName().c_str(), damage);
            wattroff(gameWin, COLOR_PAIR(7));
            wattron(gameWin, COLOR_PAIR(2));
            mvwprintw(gameWin, line++, 2, "Enemy health: %d", enemy.getHealthPoints());
            wattroff(gameWin, COLOR_PAIR(2));
            wrefresh(gameWin);
            
            player.inventory.weapons.getArray()[choice-1].setUses(player.inventory.weapons.getArray()[choice-1].getUses()-1);
            updateInventory();
            if(player.inventory.weapons.getArray()[choice-1].getUses()==0)
            {
                wattron(gameWin, COLOR_PAIR(8));
                mvwprintw(gameWin, line++, 2, "Your %s broke!", selectedWeapon.getName().c_str());
                wattroff(gameWin, COLOR_PAIR(8));
                player.inventory.removeWeapon();
                updateInventory();
                wrefresh(gameWin);
            }
            
            if(enemy.getHealthPoints()==0)
            {
                wattron(gameWin, COLOR_PAIR(5));
                checkCursorAndClear(gameWin, line);
                mvwprintw(gameWin, line++, 2, "You defeated the enemy!");
                wattroff(gameWin, COLOR_PAIR(5));
                wrefresh(gameWin);
                combatEnded = true;
                continue;
            }
        }
        checkCursorAndClear(gameWin, line);
        isEnemyTurn=!isEnemyTurn;
    }
    line++;
    heading="=== COMBAT ENDED ===";
    x=(maxX-heading.length())/2;
    wattron(gameWin, COLOR_PAIR(10));
    mvwprintw(gameWin, line++, x, heading.c_str());
    wattroff(gameWin, COLOR_PAIR(10));
    line++;
    mvwprintw(gameWin, line++, 2, "Press any key to continue...");
    wrefresh(gameWin);
    wgetch(gameWin);
}

void Dungeon::move()
{
    werase(gameWin);
    box(gameWin, 0, 0);
    mvwprintw(gameWin, 0, 2, "Game");
    bool hasMoved=false;
    int line=1;
    while(!hasMoved)
    {
        wattron(gameWin, COLOR_PAIR(1));
        mvwprintw(gameWin, line++, 2, "Where do you want to move now?");
        wattroff(gameWin, COLOR_PAIR(1));
        wattron(gameWin, COLOR_PAIR(6));
        mvwprintw(gameWin, line++, 2, "1. Move to next room");
        mvwprintw(gameWin, line++, 2, "2. Move to previous room");
        wattroff(gameWin, COLOR_PAIR(6));
        wattron(gameWin, COLOR_PAIR(1));
        mvwprintw(gameWin, line++, 2, "Choose an option (1 or 2): ");
        wattroff(gameWin, COLOR_PAIR(1));
        wrefresh(gameWin);
        int choice;
        wscanw(gameWin, "%d", &choice);
        box(gameWin, 0, 0);
        wrefresh(gameWin);
        
        switch(choice)
        {
            case 1:
            if(current->next)
            {
                if(player.inventory.hasKey(current->next->getRoomNumber()-1))
                {
                    wattron(gameWin, COLOR_PAIR(5));
                    mvwprintw(gameWin, line++, 2, "You have completed room %d", current->getRoomNumber());
                    wattroff(gameWin, COLOR_PAIR(5));
                    current = current->next;
                    wattron(gameWin, COLOR_PAIR(1));
                    mvwprintw(gameWin, line++, 2, "You moved to room %d", current->getRoomNumber());
                    wattroff(gameWin, COLOR_PAIR(1));
                    updateStatus();
                    wrefresh(gameWin);
                    hasMoved = true;
                }
                else
                {
                    wattron(gameWin, COLOR_PAIR(6));
                    mvwprintw(gameWin, line++, 2, "You need a key to enter this room. Try going a different way.");
                    wattroff(gameWin, COLOR_PAIR(6));
                    wrefresh(gameWin);
                }
            }
            else
            {
                wattron(gameWin, COLOR_PAIR(8));
                mvwprintw(gameWin, line++, 2, "You are already in the last room. Please choose another direction.");
                wattroff(gameWin, COLOR_PAIR(8));
                wrefresh(gameWin);
            }
            break;

            case 2:
            if(current->prev)
            {
                wattron(gameWin, COLOR_PAIR(5));
                mvwprintw(gameWin, line++, 2, "You have completed room %d", current->getRoomNumber());
                wattroff(gameWin, COLOR_PAIR(5));
                current=current->prev;
                wattron(gameWin, COLOR_PAIR(1));
                mvwprintw(gameWin, line++, 2, "You moved to room %d", current->getRoomNumber());
                wattroff(gameWin, COLOR_PAIR(1));
                updateStatus();
                wrefresh(gameWin);
                hasMoved = true;
            }
            else
            {
                wattron(gameWin, COLOR_PAIR(8));
                mvwprintw(gameWin, line++, 2, "You are already in the first room. Please choose another direction.");
                wattroff(gameWin, COLOR_PAIR(8));
                wrefresh(gameWin);
            }
            break;
            
            default:
            wattron(gameWin, COLOR_PAIR(9));
            mvwprintw(gameWin, line++, 2, "Invalid choice. Please select 1 or 2.");
            wattroff(gameWin, COLOR_PAIR(9));
            wrefresh(gameWin);
        }
    }
}

void Dungeon::checkCursorAndClear(WINDOW* win, int& line)
{
    int y, x;
    getyx(win, y, x);
    int maxY, maxX;
    getmaxyx(win, maxY, maxX);
    if(line>=(maxY-1))
    {
        werase(win);
        box(win, 0, 0);
        wrefresh(win);
        line=1;
    }
}

void Dungeon::playGame()
{
    int maxY, maxX;
    getmaxyx(gameWin, maxY, maxX);
    int line;

    while(true)
    {
        line=1;
        werase(gameWin);
        box(gameWin, 0, 0);
        mvwprintw(gameWin, 0, 2, "Game");
        string roomHeading="===== ROOM " + to_string(current->getRoomNumber()) + " =====";
        int startX=(maxX-roomHeading.length())/2;
        wattron(gameWin, COLOR_PAIR(5));
        mvwprintw(gameWin, line++, startX, roomHeading.c_str());
        wattroff(gameWin, COLOR_PAIR(5));
        line++;
        mvwprintw(gameWin, line++, 2, "Press any key to enter...");
        wrefresh(gameWin);
        wgetch(gameWin);

        while(!current->roomElements.isEmpty())
        {
            auto element=current->roomElements.dequeue();
            werase(gameWin);
            box(gameWin, 0, 0);
            mvwprintw(gameWin, 0, 2, "Game");
            if(Enemy* enemy=dynamic_cast<Enemy*>(element))
            {
                Enemy enemyCopy=*enemy;
                fightEnemy(enemyCopy);
                line=1;
                werase(gameWin);
                box(gameWin, 0, 0);
                mvwprintw(gameWin, 0, 2, "Game");
                updateInventory();
                if(player.inventory.foods.getSize()!=-1 && !start->next->next->getRoomCompleted())
                {
                    checkCursorAndClear(gameWin, line);
                    wattron(gameWin, COLOR_PAIR(1));
                    mvwprintw(gameWin, line++, 2, "Player health: %d", player.getHealth());
                    wattroff(gameWin, COLOR_PAIR(1));
                    wattron(gameWin, COLOR_PAIR(4));
                    mvwprintw(gameWin, line++, 2, "Do you want to use a food item (y/n)? ");
                    wattroff(gameWin, COLOR_PAIR(4));
                    wrefresh(gameWin);
                    char choice;
                    wscanw(gameWin, " %c", &choice);
                    box(gameWin, 0, 0);
                    wrefresh(gameWin);
                    while(choice!='y' && choice!='n' && choice!='Y' && choice!='N')
                    {
                        checkCursorAndClear(gameWin, line);
                        wattron(gameWin, COLOR_PAIR(9));
                        mvwprintw(gameWin, line++, 2, "Invalid choice. Please enter 'y' or 'n': ");
                        wattroff(gameWin, COLOR_PAIR(9));
                        wrefresh(gameWin);
                        wscanw(gameWin, " %c", &choice);
                        box(gameWin, 0, 0);
                        wrefresh(gameWin);
                    }
                    if(choice=='y' || choice=='Y')
                    {
                        checkCursorAndClear(gameWin, line);
                        wattron(gameWin, COLOR_PAIR(4));
                        mvwprintw(gameWin, line++, 2, "Choose a food item (1-%d): ", player.inventory.foods.getSize()+1);
                        wattroff(gameWin, COLOR_PAIR(4));
                        wrefresh(gameWin);
                        int foodChoice;
                        wscanw(gameWin, "%d", &foodChoice);
                        box(gameWin, 0, 0);
                        wrefresh(gameWin);
                        if(foodChoice < 1 || foodChoice > player.inventory.foods.getSize()+1)
                        {
                            wattron(gameWin, COLOR_PAIR(9));
                            mvwprintw(gameWin, line++, 2, "Invalid choice. You don't get any food and stay hungry!");
                            wattroff(gameWin, COLOR_PAIR(9));
                            wrefresh(gameWin);
                            continue;
                        }
                        Food selectedFood=player.inventory.foods.getArray()[foodChoice-1];
                        player.setHealth(min(player.getHealth()+selectedFood.getHealth(), 100));
                        player.inventory.foods.getArray()[foodChoice-1].setCount(selectedFood.getCount()-1);
                        updateStatus();
                        if(player.inventory.foods.getArray()[foodChoice-1].getCount()==0)
                        {
                            wattron(gameWin, COLOR_PAIR(4));
                            mvwprintw(gameWin, line++, 2, "Your %s is finished!", selectedFood.getName().c_str());
                            wattroff(gameWin, COLOR_PAIR(4));
                            player.inventory.removeFood();
                            updateInventory();
                            wrefresh(gameWin);
                        }
                    }
                    else if(choice=='n' || choice=='N')
                    {
                        wattron(gameWin, COLOR_PAIR(1));
                        mvwprintw(gameWin, line++, 2, "You chose not to use a food item. You stay hungry!");
                        wattroff(gameWin, COLOR_PAIR(1));
                        wrefresh(gameWin);
                    }
                }
                updateInventory();
            }
            else if(Weapon* weapon = dynamic_cast<Weapon*>(element))
            {
                wattron(gameWin, COLOR_PAIR(3));
                line=1;
                mvwprintw(gameWin, line++, 2, "You found a %s!", weapon->getName().c_str());
                wattroff(gameWin, COLOR_PAIR(3));
                mvwprintw(gameWin, line++, 2, "Do you want to pick it up (y/n)? ");
                wrefresh(gameWin);
                char choice;
                wscanw(gameWin, " %c", &choice);
                box(gameWin, 0, 0);
                wrefresh(gameWin);
                while(choice!='y' && choice!='n' && choice!='Y' && choice!='N')
                {
                    checkCursorAndClear(gameWin, line);
                    wattron(gameWin, COLOR_PAIR(9));
                    mvwprintw(gameWin, line++, 2, "Invalid choice. Please enter 'y' or 'n': ");
                    wattroff(gameWin, COLOR_PAIR(9));
                    wrefresh(gameWin);
                    wscanw(gameWin, " %c", &choice);
                    box(gameWin, 0, 0);
                    wrefresh(gameWin);
                }
                if(choice=='y' || choice=='Y')
                {
                    player.inventory.addWeapon(*weapon);
                    wattron(gameWin, COLOR_PAIR(3));
                    mvwprintw(gameWin, line++, 2, "You picked up the %s!", weapon->getName().c_str());
                    wattroff(gameWin, COLOR_PAIR(3));
                    updateInventory();
                    werase(gameWin);
                    box(gameWin, 0, 0);
                    mvwprintw(gameWin, 0, 2, "Game");
                    wrefresh(gameWin);
                }
                else if(choice=='n' || choice=='N')
                {
                    mvwprintw(gameWin, line++, 2, "You left the weapon behind.");
                    werase(gameWin);
                    box(gameWin, 0, 0);
                    mvwprintw(gameWin, 0, 2, "Game");
                    wrefresh(gameWin);
                }
            }
            else if(Food* food = dynamic_cast<Food*>(element))
            {
                line=1;
                wattron(gameWin, COLOR_PAIR(4));
                mvwprintw(gameWin, line++, 2, "You found a %s!", food->getName().c_str());
                wattroff(gameWin, COLOR_PAIR(4));
                mvwprintw(gameWin, line++, 2, "Do you want to pick it up (y/n)? ");
                wrefresh(gameWin);
                char choice;
                wscanw(gameWin, " %c", &choice);
                box(gameWin, 0, 0);
                wrefresh(gameWin);
                while(choice!='y' && choice!='n' && choice!='Y' && choice!='N')
                {
                    checkCursorAndClear(gameWin, line);
                    wattron(gameWin, COLOR_PAIR(9));
                    mvwprintw(gameWin, line++, 2, "Invalid choice. Please enter 'y' or 'n': ");
                    wattroff(gameWin, COLOR_PAIR(9));
                    wrefresh(gameWin);
                    wscanw(gameWin, " %c", &choice);
                    box(gameWin, 0, 0);
                    wrefresh(gameWin);
                }
                if(choice=='y' || choice=='Y')
                {
                    player.inventory.addFood(*food);
                    mvwprintw(gameWin, line++, 2, "You picked up the %s!", food->getName().c_str());
                    updateInventory();
                    werase(gameWin);
                    box(gameWin, 0, 0);
                    mvwprintw(gameWin, 0, 2, "Game");
                    wrefresh(gameWin);
                }
                else if(choice=='n' || choice=='N')
                {
                    mvwprintw(gameWin, line++, 2, "You left the food behind.");
                    werase(gameWin);
                    box(gameWin, 0, 0);
                    mvwprintw(gameWin, 0, 2, "Game");
                    wrefresh(gameWin);
                }
            }
            delete element;
        }
        checkCursorAndClear(gameWin, line);
        line++;
        wattron(gameWin, COLOR_PAIR(5));
        mvwprintw(gameWin, line++, 2, "Room %d is now completed.", current->getRoomNumber());
        wattroff(gameWin, COLOR_PAIR(5));
        mvwprintw(gameWin, line++, 2, "Press any key to continue...");
        wrefresh(gameWin);
        wgetch(gameWin);
        current->setRoomCompleted();
        if(current->next)
        {
            player.inventory.unlockKey(current->next->getRoomNumber()-1);
            updateInventory();
        }
        if(start->next->next->getRoomCompleted())
        {
            break;
        }
        wrefresh(gameWin);
        move();
        while(current->getRoomCompleted())
        {
            mvwprintw(gameWin, line++, 2, "You have already completed this room. Please choose another direction.");
            wrefresh(gameWin);
            move();
        }
    }
    checkCursorAndClear(gameWin, line);
    wattron(gameWin, COLOR_PAIR(5));
    mvwprintw(gameWin, line++, 2, "Congratulations! You have completed the dungeon!");
    wattroff(gameWin, COLOR_PAIR(5));
    mvwprintw(gameWin, line++, 2, "Press any key to exit... ");
    wrefresh(gameWin);
    wgetch(gameWin);
}