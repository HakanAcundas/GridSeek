#pragma once
#include "tile.hpp"

class ForestTile : public Tile {
public:
    ForestTile(glm::vec2 coordinate) : Tile(TileType::Forest), coord(coordinate) {};
    ForestTile(int x, int y) : Tile(TileType::Forest), coord(glm::vec2(x, y)) {};
    void draw() override;

    // getters and setters
    glm::vec2 get_coordinate() { return coord; }
    void set_coordinate(glm::vec2 new_coord) { coord = new_coord; } 
private:
    glm::vec2 coord;
    const char* texture = "F";
};
