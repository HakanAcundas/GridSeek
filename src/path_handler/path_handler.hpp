#pragma once

#include <vector>
#include <array>
#include <memory>
#include <algorithm>
#include <queue>
#include "../../shared/global_settings.hpp"
#include "../map/tile.hpp"

class PathHandler
{
public:
    PathHandler();
    int minCost(std::array<std::array<std::shared_ptr<Tile>, MAP_WIDTH>, MAP_HEIGHT>& map, glm::vec2 start, glm::vec2 target);

    struct Node
    {
        int row, col, cost;
        Node(int r, int c, int co) : row(r), col(c), cost(co) {}
    };

    struct CompareCost
    {
        bool operator()(const Node& n1, const Node& n2) const
        {
            return n1.cost > n2.cost; // min-heap
        }
    };
private:
    std::priority_queue<Node, std::vector<Node>, CompareCost> pq;
};
