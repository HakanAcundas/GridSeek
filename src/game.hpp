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

class Game {
public:
    Game();
    ~Game() {};

    DPErrorCode init();
    void run();
    DPErrorCode genarate_map();
    DPErrorCode create_target();
    DPErrorCode print_map();
    DPErrorCode bind_input();

    // Getters
    bool is_running()           { return running; }
    int get_map_height()        { return MAP_HEIGHT; }
    int get_map_widht()         { return MAP_WIDTH; }
    glm::vec2 get_map_vector()  { return glm::vec2(MAP_HEIGHT, MAP_WIDTH); }
    std::vector<Target> get_targets()   { return targets; }

    // Setters
    void set_running() { running = !running; }

private:
    bool running = false;
    Player player;
    std::vector<Target> targets;

    std::array<std::array<std::shared_ptr<Tile>, MAP_WIDTH>, MAP_HEIGHT> map;
};