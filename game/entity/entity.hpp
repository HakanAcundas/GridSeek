#pragma once
#include <glm/glm.hpp>

class Entity {
public:
    virtual ~Entity() {};
    virtual void move(glm::vec2 direction) = 0;
    virtual void attack() = 0;

    glm::vec2 get_position() { return position; }
protected:
    glm::vec2 position;
};