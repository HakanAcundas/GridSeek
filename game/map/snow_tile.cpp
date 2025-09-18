#include <iostream>
#include "snow_tile.hpp"

#define DEFAULT_SNOW_MOVEMENT_COST 3

SnowTile::SnowTile(glm::vec2 coordinate) :  Tile(TileType::Snow, DEFAULT_SNOW_MOVEMENT_COST), coord(coordinate) {}

SnowTile::SnowTile(int x, int y) :  Tile(TileType::Snow, DEFAULT_SNOW_MOVEMENT_COST), coord(glm::vec2(x, y)) {}

void SnowTile::draw() {
    std::cout << texture;
}