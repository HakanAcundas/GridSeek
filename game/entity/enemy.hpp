#pragma once
#include "entity.hpp"

#define DEFAULT_HP      100
#define DEFAULT_DAMAGE  20

class Enemy : public Entity {
public:
    Enemy();
    Enemy(unsigned int damage, unsigned int hp);
    
    void move(glm::vec2 direction) override;
    void attack() override;

private:
    unsigned int id, damage, hp;  
};