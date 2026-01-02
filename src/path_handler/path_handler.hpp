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
    PathHandler(std::array<std::array<std::unique_ptr<Tile>, MAP_HEIGHT>, MAP_WIDTH>& map);
    ~PathHandler() = default;

    int find_shortest_path(glm::ivec2 start, std::vector<glm::ivec2> target_positions);
    int dijkstra(glm::ivec2 start, glm::ivec2 target);
    int a_star(glm::ivec2 start, glm::ivec2 target);
    void rebuild_shortest_path(glm::ivec2 start, glm::ivec2 target);
    int taxicap_distance(glm::ivec2 left, glm::ivec2 right);

    struct Node
    {
        int x, y, cost;
        int tentative_score; // Needed for A* algorithm
        bool touched = false;
        Node(int x, int y, int co) : x(x), y(y), cost(co), tentative_score(0){}
        Node(int x, int y, int co, int tc) : x(x), y(y), cost(co), tentative_score(tc) {}
    };

    struct CompareCost
    {
        bool operator()(Node& n1, Node& n2) const
        {
            return n1.cost > n2.cost; // min-heap
        }
    };

    struct CompareTentativeScore
    {
        bool operator()(Node& n1, Node& n2) const
        {
            return n1.tentative_score > n2.tentative_score;
        }
    };

private:
    std::array<std::array<std::unique_ptr<Tile>, MAP_HEIGHT>, MAP_WIDTH>& map;
    int dist[MAP_WIDTH][MAP_HEIGHT];
    glm::ivec2 prev[MAP_WIDTH][MAP_HEIGHT];
};
