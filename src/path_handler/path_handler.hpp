#include <vector>
#include <array>
#include <memory>
#include <algorithm>
#include <queue>
#include "../../shared/global_settings.hpp"
#pragma once

#include "../map/tile.hpp"

class PathHandler
{
public:
    PathHandler();
    int minCost(std::array<std::array<std::shared_ptr<Tile>, MAP_WIDTH>, MAP_HEIGHT>& map, glm::vec2 start, glm::vec2 target);
private:
    std::priority_queue pq;
};
