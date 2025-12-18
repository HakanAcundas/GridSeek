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
    int dijkstra(std::array<std::array<std::unique_ptr<Tile>, MAP_HEIGHT>, MAP_WIDTH>& map, 
        glm::ivec2 start, glm::ivec2 target);
    void rebuild_shortest_path(std::array<std::array<std::unique_ptr<Tile>, MAP_HEIGHT>, MAP_WIDTH>& map,
        glm::ivec2 start, glm::ivec2 target);

    struct Node
    {
        int x, y, cost;
        bool touched = false;
        Node(int x, int y, int co) : x(x), y(y), cost(co) {}
    };

    struct CompareCost
    {
        bool operator()(Node& n1, Node& n2) const
        {
            return n1.cost > n2.cost; // min-heap
        }
    };
private:
    int dist[MAP_WIDTH][MAP_HEIGHT];
    glm::ivec2 prev[MAP_WIDTH][MAP_HEIGHT];
    std::priority_queue<Node, std::vector<Node>, CompareCost> pq;
};
