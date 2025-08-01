#include "Enemy.hpp"

Enemy::Enemy(string name, int attackPower, int healthPoints) : name(name), attackPower(attackPower), healthPoints(healthPoints) {}

int Enemy::getAttackPower() const {return attackPower;}

int Enemy::getHealthPoints() const {return healthPoints;}

string Enemy::getName() const {return name;}

void Enemy::setHealthPoints(int healthPoints) {this->healthPoints=healthPoints;}