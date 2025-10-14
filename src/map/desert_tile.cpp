#include <iostream>
#include <Windows.h>
#include "desert_tile.hpp"

#define DEFAULT_FOREST_MOVEMENT_COST 4

DesertTile::DesertTile(glm::vec2 coordinate) : Tile(TileType::Forest, DEFAULT_FOREST_MOVEMENT_COST), coord(coordinate) {}

DesertTile::DesertTile(int x, int y) : Tile(TileType::Forest, DEFAULT_FOREST_MOVEMENT_COST), coord(glm::vec2(x, y)) {}

void DesertTile::draw() {
    HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hc, 0x02);
    std::cout << texture;
    SetConsoleTextAttribute(hc, 0x07);
}