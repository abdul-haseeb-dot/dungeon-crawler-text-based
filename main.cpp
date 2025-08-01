#include<curses.h>
#include<ctime>
#include<cstdlib>
#include "Dungeon.hpp"

int main()
{
    initscr();
    cbreak();
    echo();
    
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);    //For default text
    init_pair(2, COLOR_RED, COLOR_BLACK);      //For enemies
    init_pair(3, COLOR_CYAN, COLOR_BLACK);     //For weapons
    init_pair(4, COLOR_GREEN, COLOR_BLACK);    //For foods
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);   //For success/unlocked
    init_pair(6, COLOR_MAGENTA, COLOR_BLACK);  //For locked
    init_pair(7, COLOR_GREEN, COLOR_BLACK);    //For high health
    init_pair(8, COLOR_YELLOW, COLOR_BLACK);   //For medium health
    init_pair(9, COLOR_RED, COLOR_BLACK);      //For low health
    init_pair(10, COLOR_BLUE, COLOR_BLACK);    //For combat messages
    
    srand(time(0));
    Dungeon dungeon;

    auto fillRoom1 = [&dungeon]()
    {
        dungeon.getStart()->roomElements.enqueue(new Weapon("Sword"));
        dungeon.getStart()->roomElements.enqueue(new Weapon("Bow"));
        dungeon.getStart()->roomElements.enqueue(new Enemy("Goblin", 25, 10));
        dungeon.getStart()->roomElements.enqueue(new Food("Apple"));
        dungeon.getStart()->roomElements.enqueue(new Enemy("Bat", 20, 10));
    };

    auto fillRoom2 = [&dungeon]()
    {
        dungeon.getStart()->next->roomElements.enqueue(new Enemy("Orc", 35, 15));
        dungeon.getStart()->next->roomElements.enqueue(new Food("Peach"));
        dungeon.getStart()->next->roomElements.enqueue(new Weapon("Grenade"));
        dungeon.getStart()->next->roomElements.enqueue(new Food("Dinner"));
        dungeon.getStart()->next->roomElements.enqueue(new Enemy("Bat", 20, 10));
        dungeon.getStart()->next->roomElements.enqueue(new Enemy("Sphinx", 25, 15));
        dungeon.getStart()->next->roomElements.enqueue(new Weapon("Mace"));
    };

    auto fillRoom3 = [&dungeon]()
    {
        dungeon.getStart()->next->next->roomElements.enqueue(new Food("Potion"));
        dungeon.getStart()->next->next->roomElements.enqueue(new Enemy("Chimera", 30, 30));
        dungeon.getStart()->next->next->roomElements.enqueue(new Enemy("Dragon", 45, 150));
    };

    auto startingProtocol = [&dungeon]()
    {
        werase(dungeon.gameWin);
        box(dungeon.gameWin, 0, 0);
        mvwprintw(dungeon.gameWin, 0, 2, "Game");
        wattron(dungeon.gameWin, COLOR_PAIR(5));
        mvwprintw(dungeon.gameWin, 1, 2, "Welcome to the Dungeon Crawler Game!");
        mvwprintw(dungeon.gameWin, 2, 2, "You may or may not get out alive!");
        mvwprintw(dungeon.gameWin, 3, 2, "You must complete three rooms to win the game!");
        mvwprintw(dungeon.gameWin, 5, 2, "To choose weapons or food, please enter the number of the item to choose.");
        mvwprintw(dungeon.gameWin, 6, 2, "Only use 'y' or 'n' for yes or no.");
        mvwprintw(dungeon.gameWin, 7, 2, "You can use food items to restore your health after fighting an enemy.");
        mvwprintw(dungeon.gameWin, 9, 2, "Good luck! May the odds be in your favor");
        wattroff(dungeon.gameWin, COLOR_PAIR(5));
        mvwprintw(dungeon.gameWin, 11, 2, "Press any key to continue...");
        wrefresh(dungeon.gameWin);
        wgetch(dungeon.gameWin);
        werase(dungeon.gameWin);
        box(dungeon.gameWin, 0, 0);
        wrefresh(dungeon.gameWin);
    };

    fillRoom1();
    fillRoom2();
    fillRoom3();

    startingProtocol();
    try
    {
        dungeon.playGame();
    }
    catch(const exception& e)
    {
        werase(dungeon.gameWin);
        box(dungeon.gameWin, 0, 0);
        mvwprintw(dungeon.gameWin, 0, 2, "Game");
        wattron(dungeon.gameWin, COLOR_PAIR(9));
        mvwprintw(dungeon.gameWin, 1, 2, "%s", e.what());
        mvwprintw(dungeon.gameWin, 2, 2, "Press any key to exit...");
        wattroff(dungeon.gameWin, COLOR_PAIR(9));
        wrefresh(dungeon.gameWin);
        wgetch(dungeon.gameWin);
    }
    
    endwin();
    return 0;
}