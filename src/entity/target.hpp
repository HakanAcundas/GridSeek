#pragma once
#include <glm/glm.hpp>
#include "entity.hpp"

class Target : public Entity
{
public:
    bool is_visited = false;
    
    Target(int posX, int posY);
    ~Target() override;

    void move(glm::ivec2 direction) override;
    void attack() override;
    void draw();
    
private:
    unsigned int id;
    const char* texture = "T";
};