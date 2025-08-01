#ifndef DUNGEON_HPP
#define DUNGEON_HPP

#include "Player.hpp"
#include "Room.hpp"
#include "Enemy.hpp"
#include<curses.h>

class Dungeon
{
    private:
    Player player;
    Room* current;
    Room* start;
    WINDOW* menuWin;
    WINDOW* inventoryWin;
    WINDOW* statusWin;

    public:
    WINDOW* gameWin;

    Dungeon();
    ~Dungeon();
    Room* getStart() const;
    void updateMenu();
    void updateInventory();
    void updateStatus();
    void fightEnemy(Enemy enemy);
    void move();
    void checkCursorAndClear(WINDOW* win, int& line);
    void playGame();
};

#endif