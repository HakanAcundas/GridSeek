#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include "game.hpp"
#include "command.hpp"
#include "input.hpp"
#include "map/forest_tile.hpp"
#include "map/snow_tile.hpp"

using namespace input;

Game::Game() {
    init();
}

DPErrorCode Game::init() {
    // Random device and distribution.
    std::random_device rdevice;
    std::mt19937 rng(rdevice());
    std::uniform_int_distribution<std::mt19937::result_type> dist3(1,2);

    // Filling map model.
    for (int column = 0; column < MAP_HEIGHT; column++) {
        for (int row = 0; row < MAP_WIDTH; row++) {
            unsigned int random_tile = dist3(rng);
            switch (random_tile)
            {
                case 1: map.at(column).at(row) = std::make_unique<ForestTile>(glm::vec2(row, column));
                break;
                case 2: map.at(column).at(row) = std::make_unique<SnowTile>(glm::vec2(row, column));
                break;
            }
        }
    }

    try {
        Input *input  = &Input::get_instance();
        input->bind('w', std::make_unique<MoveCommand>(glm::vec2(-1,0)));
        input->bind('s', std::make_unique<MoveCommand>(glm::vec2(1,0)));
        input->bind('d', std::make_unique<MoveCommand>(glm::vec2(0,1)));
        input->bind('a', std::make_unique<MoveCommand>(glm::vec2(0,-1)));
    } catch(const std::exception& e) { 
        "Unable to bind keyboard commands!"; 
    }

    return DPErrorCode::SUCCESS;
}

DPErrorCode Game::print_map() {

    for (int column = 0; column < MAP_HEIGHT; column++) {
        for (int row =0; row < MAP_WIDTH; row++) {
            if (player.get_position() == glm::vec2(column, row)) {
                std::cout << 'T';
                continue;
            }
            map.at(column).at(row)->draw();
        }
        std::cout << "\n";
    }

    return DPErrorCode::SUCCESS;
}

void Game::run() {
    set_running();
    while (is_running()) {
        Command *command = Input::get_instance().handle_input();
        CLEARSCREEN;
        if (command) {
            command->execute(player);
        }
        print_map();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}