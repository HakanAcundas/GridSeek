#pragma once
#include <glm/glm.hpp>

enum struct TileType {
    Forest,
    Snow,
    Desert
};

class Tile {
public:
    Tile() : ttype(TileType::Forest) {}
    Tile(TileType type) : ttype(type) {}
    ~Tile() {}
    virtual void draw() = 0;

    // getters and setters
    TileType get_tile_type() { return ttype; }
    void set_tile_type(TileType new_ttype) { ttype = new_ttype; }
    int get_movement_cost() { return movement_cost; }
    void set_movement_cost(int new_mcost) { movement_cost = new_mcost; }
protected:
    TileType ttype;
    int movement_cost = 1;
};