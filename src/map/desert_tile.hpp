#pragma once
#include "tile.hpp"

class DesertTile : public Tile {
public:
    DesertTile(glm::vec2 coordinate);
    DesertTile(int x, int y);
    void draw() override;

    // getters and setters
    glm::ivec2 get_coordinate() { return coord; }
    void set_coordinate(glm::vec2 new_coord) { coord = new_coord; } 
private:
    glm::ivec2 coord;
    const char* texture = "F";
};
