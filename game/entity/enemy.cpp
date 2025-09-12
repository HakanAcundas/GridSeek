#include <iostream>
#include "enemy.hpp"

Enemy::Enemy() {
    damage = DEFAULT_DAMAGE;
    hp = DEFAULT_HP;
}

Enemy::Enemy(unsigned int damage, unsigned int hp) : damage(damage), hp(hp) {}

void Enemy::move(glm::vec2 direction) {
    std::cout << "Enemy moved!\n";
}

void Enemy::attack() {
    std::cout << "Enemy attacked!\n";
}
