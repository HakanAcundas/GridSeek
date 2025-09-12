#pragma once
#include <glm/glm.hpp>
#include "entity.hpp"

#define DEFAULT_SPEED 1     // (1,1) as vec2
#define DEFAULT_JUMP_POWER 1
#define DEFAULT_POSITION 0  // (0,0) as vec2

class Player : public Entity{
public:
    Player();
    Player(int posX, int posY);
    ~Player() override;

    void move(glm::vec2 direction) override;
    void attack() override;
private:
    glm::vec2 speed;
    int jump_power;
};