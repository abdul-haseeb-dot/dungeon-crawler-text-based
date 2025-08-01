#include "Player.hpp"

Player::Player() : health(100) {}

int Player::getHealth() const {return health;}

void Player::setHealth(int health) {this->health=health;}

void Player::displayPlayerHealth() const
{
    attron(COLOR_PAIR(1));
    printw("Player Health: ");
    attroff(COLOR_PAIR(1));
    attron(COLOR_PAIR(health > 50 ? 7 : (health > 20 ? 8 : 9)));
    printw("%d\n", health);
    attroff(COLOR_PAIR(health > 50 ? 7 : (health > 20 ? 8 : 9)));
}