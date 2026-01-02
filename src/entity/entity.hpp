#pragma once

#include <glm/glm.hpp>

class Entity {
public:
    virtual ~Entity() {};
    glm::ivec2 get_position() { return position; }
protected:
    glm::ivec2 position;
};