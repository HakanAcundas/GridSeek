#pragma once
#include "tile.hpp"

class SnowTile : public Tile {
public:
    SnowTile(glm::ivec2 coordinate);
    SnowTile(int x, int y);
    ~SnowTile() override {}
    void draw() override;

    // getters and setters
    glm::ivec2 get_coordinate() { return coord; }
    void set_coordinate(glm::ivec2 new_coord) { coord = new_coord; } 
private:
    glm::ivec2 coord;
    char texture = TEXTURE_SNOW;
};
