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
    DPErrorCode code = genarate_map(); 
    if (code != DPErrorCode::SUCCESS) {
        return code;
    }

    code = bind_input();
    if (code != DPErrorCode::SUCCESS) {
        return code;
    }

    return DPErrorCode::SUCCESS;
}

DPErrorCode Game::genarate_map() {
    // Random device and distribution.
    std::random_device rdevice;
    std::mt19937 rng(rdevice());
    std::uniform_int_distribution<std::mt19937::result_type> dist_tile(1,2);

    unsigned int remaining_height = MAP_HEIGHT;
    unsigned int remaining_width  = MAP_WIDTH;

    unsigned int startY = 0;  // where the current blob starts vertically
    unsigned int startX = 0;  // where the current blob starts horizontally

    try {
        while (remaining_height > 0) {
            // Blob size distribution
            std::uniform_int_distribution<std::mt19937::result_type> dist_blob_size(2, 5);

            // Choose a random blob height
            unsigned int blob_height = dist_blob_size(rng);
            if (blob_height > remaining_height) {
                blob_height = remaining_height;
            }

            // Reset X for each new row section
            remaining_width = MAP_WIDTH;
            startX = 0;

            while (remaining_width > 0) {
                // Choose a random blob width
                unsigned int blob_width = dist_blob_size(rng);
                if (blob_width > remaining_width) {
                    blob_width = remaining_width;
                }

                unsigned int blob_type = dist_tile(rng);
                // Fill the blob
                for (unsigned int row = 0; row < blob_height; ++row) {
                    for (unsigned int col = 0; col < blob_width; ++col) {
                        unsigned int x = startX + col;
                        unsigned int y = startY + row;

                        switch (blob_type) {
                            case 1:
                                map.at(y).at(x) = std::make_unique<ForestTile>(glm::vec2(x, y));
                                break;
                            case 2:
                                map.at(y).at(x) = std::make_unique<SnowTile>(glm::vec2(x, y));
                                break;
                        }
                    }
                }

                // Move right for the next blob
                startX += blob_width;
                remaining_width -= blob_width;
            }

            // Move down for the next row of blobs
            startY += blob_height;
            remaining_height -= blob_height;
        }
    }
    catch(const std::exception& e) { 
        "Unable to bind keyboard commands!"; 
        return DPErrorCode::MAP_GENERATION_ERROR;
    }
    
    return DPErrorCode::SUCCESS;
}

DPErrorCode Game::print_map() {

    for (int column = 0; column < MAP_HEIGHT; column++) {
        for (int row = 0; row < MAP_WIDTH; row++) {
            if (player.get_position() == glm::vec2(column, row)) {
                player.draw();
                continue;
            }
            
            for (Target target : targets) {
                glm::vec2 target_pos = target.get_position();
                if (target_pos == glm::vec2(column, row)) {
                    target.draw();
                }
            }
            map.at(column).at(row)->draw();
            // std::cout << map.at(column).at(row)->get_movement_cost();
        }
        std::cout << "\n";
    }

    return DPErrorCode::SUCCESS;
}

DPErrorCode Game::bind_input() {
    try {
        Input *input  = &Input::get_instance();
        input->bind('w', std::make_unique<MoveCommand>(glm::vec2(-1,0)));
        input->bind('s', std::make_unique<MoveCommand>(glm::vec2(1,0)));
        input->bind('d', std::make_unique<MoveCommand>(glm::vec2(0,1)));
        input->bind('a', std::make_unique<MoveCommand>(glm::vec2(0,-1)));
    } catch(const std::exception& e) { 
        return DPErrorCode::INPUT_BINDING_ERROR;
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