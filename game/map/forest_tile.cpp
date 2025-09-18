#include <iostream>
#include "forest_tile.hpp"

#define DEFAULT_FOREST_MOVEMENT_COST 2

ForestTile::ForestTile(glm::vec2 coordinate) : Tile(TileType::Forest, DEFAULT_FOREST_MOVEMENT_COST), coord(coordinate) {}

ForestTile::ForestTile(int x, int y) : Tile(TileType::Forest, DEFAULT_FOREST_MOVEMENT_COST), coord(glm::vec2(x, y)) {}

void ForestTile::draw() {
    std::cout << texture;
}