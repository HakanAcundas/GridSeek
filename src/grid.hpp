#pragma once
#include <array>
#include <vector>
#include <string>
#include <stdlib.h>
#include <memory>
#include <glm/glm.hpp>
#include "../shared/global_settings.hpp"
#include "error.hpp"
#include "entity/player.hpp"
#include "entity/target.hpp"
#include "map/tile.hpp"

#define CLEARSCREEN system ( "cls" )

class Grid {
public:
    Grid();
    ~Grid() {};

    DPErrorCode init();
    void run();
    DPErrorCode genarate_map();
    DPErrorCode create_target();
    DPErrorCode print_map();
    DPErrorCode bind_input();

    // Getters
    bool is_running()                   { return running; }
    int get_map_widht()                 { return MAP_WIDTH; }
    int get_map_height()                { return MAP_HEIGHT; }
    glm::vec2 get_map_vector()          { return glm::vec2(MAP_WIDTH, MAP_HEIGHT); }
    std::vector<Target> get_targets()   { return targets; }

    // Setters
    void set_running() { running = !running; }

private:
    bool running = false;
    Player player;
    std::vector<Target> targets;
    std::array<std::array<std::unique_ptr<Tile>, MAP_HEIGHT>, MAP_WIDTH> map;
};