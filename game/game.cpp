#include <iostream>
#include <thread>
#include <chrono>
#include "game.hpp"
#include "command.hpp"
#include "input.hpp"

using namespace input;

Game::Game() {
    init();
}

DPErrorCode Game::init() {
    // TODO: Random (seed based) tile generation (forest, snowy, river).    
    for (int column = 0; column < MAP_HEIGHT; column++) {
        for (int row = 0; row < MAP_WIDTH; row++) {
            map.at(column).at(row) = '_';
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
            std::cout << map.at(column).at(row);
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