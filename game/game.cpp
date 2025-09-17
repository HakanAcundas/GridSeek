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
    std::uniform_int_distribution<std::mt19937::result_type> dist_tile(1,2);

    unsigned int remaining_height = MAP_HEIGHT;
    unsigned int remaining_width  = MAP_WIDTH;

    unsigned int startY = 0;  // where the current blob starts vertically
    unsigned int startX = 0;  // where the current blob starts horizontally

    while (remaining_height > 0) {
        // Blob size distribution
        std::uniform_int_distribution<std::mt19937::result_type> dist_blob_size(2, 5);

        unsigned int blob_height = dist_blob_size(rng);
        if (blob_height > remaining_height) {
            blob_height = remaining_height;
        }

        // reset X for each new row section
        remaining_width = MAP_WIDTH;
        startX = 0;

        while (remaining_width > 0) {
            // choose a random blob width (clamped)
            unsigned int blob_width = dist_blob_size(rng);
            if (blob_width > remaining_width) {
                blob_width = remaining_width;
            }

            unsigned int blob_type = dist_tile(rng);
            // fill the blob
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

            // move right for the next blob
            startX += blob_width;
            remaining_width -= blob_width;
        }

        // move down for the next row of blobs
        startY += blob_height;
        remaining_height -= blob_height;
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