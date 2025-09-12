#include <iostream>
#include "player.hpp"

Player::Player() {
    position = glm::vec2(DEFAULT_POSITION);
    speed = glm::vec2(DEFAULT_SPEED);
    jump_power = DEFAULT_JUMP_POWER;
}

Player::Player(int posX, int posY) {
    position = glm::vec2(posX, posY);
    speed = glm::vec2(DEFAULT_SPEED);
    jump_power = DEFAULT_JUMP_POWER;
}

Player::~Player() {}

void Player::move(glm::vec2 direction) {
    position += direction;
}

void Player::attack() {
    std::cout << "Player attacked!\n";
}