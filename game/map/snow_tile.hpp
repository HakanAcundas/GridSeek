#pragma once
#include "tile.hpp"

class SnowTile : public Tile {
public:
    SnowTile(glm::vec2 coordinate) :  Tile(TileType::Snow), coord(coordinate) {};
    SnowTile(int x, int y) :  Tile(TileType::Snow), coord(glm::vec2(x, y)) {};
    void draw() override;

    // getters and setters
    glm::vec2 get_coordinate() { return coord; }
    void set_coordinate(glm::vec2 new_coord) { coord = new_coord; } 
private:
    glm::vec2 coord;
    const char* texture = "S";
};
