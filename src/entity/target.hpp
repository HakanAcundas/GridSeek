#pragma once
#include <glm/glm.hpp>
#include "../shared/global_settings.hpp"
#include "entity.hpp"

class Target : public Entity
{
public:
    bool is_visited = false;
    
    Target(int id, int posX, int posY);
    Target(int posX, int posY);
    ~Target() override;

    void move(glm::ivec2 direction) override;
    void attack() override;
    void draw();
    
private:
    unsigned int id;
    char texture = TEXTURE_TARGET;
};