#pragma once
#include "tile.hpp"

class ForestTile : public Tile {
public:
    ForestTile(glm::vec2 coordinate);
    ForestTile(int x, int y);
    ~ForestTile() override {}
    void draw() override;

    // getters and setters
    glm::ivec2 get_coordinate() { return coord; }
    void set_coordinate(glm::ivec2 new_coord) { coord = new_coord; } 
private:
    glm::ivec2 coord;
    char texture = TEXTURE_FOREST;
};
