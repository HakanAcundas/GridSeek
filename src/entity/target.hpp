#pragma once
#include <glm/glm.hpp>
#include "entity.hpp"

class Target : public Entity {
public:
    Target(int posX, int posY);
    ~Target() override;

    void move(glm::vec2 direction) override;
    void attack() override;
    void draw();
private:
    unsigned int id;
    const char* texture = "E";
};