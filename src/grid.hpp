#pragma once
#include <array>
#include <vector>
#include <stdlib.h>
#include <glm/glm.hpp>
#include "../shared/global_settings.hpp"
#include "error.hpp"
#include "entity/target.hpp"
#include "map/tile.hpp"

#define CLEARSCREEN system ( "cls" )

class Grid
{
public:
    using TileMap = std::array<std::array<std::unique_ptr<Tile>, MAP_HEIGHT>, MAP_WIDTH>;

    Grid();
    ~Grid() {};

    DPErrorCode init();
    void run();
    DPErrorCode genarate_map();
    DPErrorCode create_target();
    DPErrorCode print_map();

    // Getters
    bool is_running()                   { return running; }
    int get_map_widht()                 { return MAP_WIDTH; }
    int get_map_height()                { return MAP_HEIGHT; }
    glm::vec2 get_map_size()            { return glm::vec2(MAP_WIDTH, MAP_HEIGHT); }
    TileMap& get_map()                  { return map; }
    std::vector<glm::ivec2> get_targets()
    {
        std::vector<glm::ivec2> positions;
        for (Target target : targets)
            positions.push_back(target.get_position());

        return positions;
    }

    // Setters
    void set_running() { running = !running; }

private:
    bool running = false;
    std::vector<Target> targets;
    TileMap map;
};