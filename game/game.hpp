#pragma once
#include <array>
#include <string>
#include <stdlib.h>
#include <glm/glm.hpp>
#include "error.hpp"
#include "entity/player.hpp"
#include "entity/enemy.hpp"

#define CLEARSCREEN system ( "cls" )

#define MAP_WIDTH   48
#define MAP_HEIGHT  27

class Game {
public:
    Game();
    ~Game() {};

    DPErrorCode init();
    void run();
    DPErrorCode print_map();

    // Getters
    bool is_running()           { return running; } 
    int get_map_height()        { return MAP_HEIGHT; }
    int get_map_widht()         { return MAP_WIDTH; }
    glm::vec2 get_map_vector()  { return glm::vec2(MAP_HEIGHT, MAP_WIDTH); }

    // Setters
    void set_running() {running = !running; }

private:
    bool running = false;
    std::array<std::array<char, MAP_WIDTH>, MAP_HEIGHT> map;
    
    Player player;
};