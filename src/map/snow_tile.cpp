#include <iostream>
#include <Windows.h>
#include "snow_tile.hpp"

SnowTile::SnowTile(glm::ivec2 coordinate) :  Tile(TileType::Snow, SNOW_MOVEMENT_COST), coord(coordinate) {}

SnowTile::SnowTile(int x, int y) :  Tile(TileType::Snow, SNOW_MOVEMENT_COST), coord(glm::ivec2(x, y)) {}

void SnowTile::draw()
{
    HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);
    if (is_path())
    {
        SetConsoleTextAttribute(hc, 0x93);
    }
    else
    {
        SetConsoleTextAttribute(hc, 0x07);
    }
    std::cout << texture;
}
