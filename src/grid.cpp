#include <iostream>
#include <chrono>
#include <random>
#include "../shared/global_settings.hpp"
#include "grid.hpp"
#include "map/forest_tile.hpp"
#include "map/snow_tile.hpp"

Grid::Grid()
{
    init();
}

DPErrorCode Grid::init()
{
    DPErrorCode code = genarate_map(); 
    if (code != DPErrorCode::SUCCESS)
        return code;
    
    code = create_target();
    code = create_target();
    code = create_target();
    if (code != DPErrorCode::SUCCESS)
        return code;

    set_running();
    return DPErrorCode::SUCCESS;
}

DPErrorCode Grid::genarate_map()
{
    // Random device and distribution.
    std::random_device rdevice;
    std::mt19937 rng(rdevice());
    std::uniform_int_distribution<std::mt19937::result_type> dist_tile(1,2);

    unsigned int remaining_width  = MAP_WIDTH;
    unsigned int remaining_height = MAP_HEIGHT;

    unsigned int startY = 0;  // where the current blob starts vertically
    unsigned int startX = 0;  // where the current blob starts horizontally

    try {
        while (remaining_height > 0)
        {
            // Blob size distribution
            std::uniform_int_distribution<std::mt19937::result_type> dist_blob_size(2, 5);

            // Choose a random blob height
            unsigned int blob_height = dist_blob_size(rng);
            if (blob_height > remaining_height)
                blob_height = remaining_height;

            // Reset X for each new row section
            remaining_width = MAP_WIDTH;
            startX = 0;

            while (remaining_width > 0)
            {
                // Choose a random blob width
                unsigned int blob_width = dist_blob_size(rng);
                if (blob_width > remaining_width)
                    blob_width = remaining_width;

                unsigned int blob_type = dist_tile(rng);
                // Fill the blob
                for (unsigned int row = 0; row < blob_width; ++row)
                {
                    for (unsigned int col = 0; col < blob_height; ++col)
                    {
                        unsigned int x = startX + row;
                        unsigned int y = startY + col;

                        switch (blob_type)
                        {
                            case 1:
                                map.at(x).at(y) = std::make_unique<ForestTile>(glm::ivec2(x, y));
                                break;
                            case 2:
                                map.at(x).at(y) = std::make_unique<SnowTile>(glm::ivec2(x, y));
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

DPErrorCode Grid::create_target()
{
    // TODO: Set maximum number of target

    // Random device and distribution.
    std::random_device rdevice;
    std::mt19937 rng(rdevice());
    std::uniform_int_distribution<std::mt19937::result_type> rand_posx(0, MAP_WIDTH - 1);
    std::uniform_int_distribution<std::mt19937::result_type> rand_posy(0, MAP_HEIGHT - 1);
    
    glm::ivec2 position {rand_posx(rng), rand_posy(rng)};

    // Check if new position is not overlapping with the previous existing entity position and start position.
    while (position == glm::ivec2(0, 0) && targets.size() > 0 && position == targets.back().get_position())
    {
        position = glm::ivec2(rand_posx(rng), rand_posy(rng)); // Set new position.
    }

    int id = targets.size();

    Target new_target(id, position.x, position.y);
    targets.push_back(new_target);

    return DPErrorCode::SUCCESS;
}

DPErrorCode Grid::print_map() {
    for (int column = 0; column < MAP_HEIGHT; column++)
    {
        for (int row = 0; row < MAP_WIDTH; row++)
        {   
            for (Target target : targets)
            {
                glm::ivec2 target_pos = target.get_position();
                if (target_pos == glm::ivec2(row, column))
                {
                    target.draw();
                    goto cnt;
                }
            }
            map[row][column]->draw();
            cnt:;
        }
        std::cout << "\n";
    }

    return DPErrorCode::SUCCESS;
}

void Grid::run()
{
    std::vector<glm::ivec2> tpositions;
    for (Target t : targets)
    {
        tpositions.push_back(t.get_position());
    }

    print_map();
}