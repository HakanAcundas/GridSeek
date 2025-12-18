#pragma once
#include <glm/glm.hpp>

class Entity {
public:
    virtual ~Entity() {};
    virtual void move(glm::ivec2 direction) = 0;
    virtual void attack() = 0;

    glm::ivec2 get_position() { return position; }
protected:
    glm::ivec2 position;
};