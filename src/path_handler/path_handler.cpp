#include <iostream>
#include "path_handler.hpp"

PathHandler::PathHandler(std::array<std::array<std::unique_ptr<Tile>, MAP_HEIGHT>, MAP_WIDTH>& map)
    : map(map)
{
}

int PathHandler::find_shortest_path(glm::ivec2 start, std::vector<glm::ivec2> target_positions)
{
    int total_cost = 0;
    for (glm::ivec2 tpos : target_positions)
    {
        total_cost += a_star(start, tpos);
        rebuild_shortest_path(start, tpos);
        start = tpos;
    }

    return total_cost;
}

// Pseudocode: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm#Pseudocode
int PathHandler::dijkstra(glm::ivec2 start, glm::ivec2 target)
{
    std::priority_queue<Node, std::vector<Node>, CompareCost> pq;

    int sx = start.x;
    int sy = start.y;
    int tx = target.x;
    int ty = target.y;

    // First start from "start" position
    dist[sx][sy] = 0;
    pq.push(Node(sx, sy, 0));

    // Initilition of nodes
    for (int x = 0; x < MAP_WIDTH; x++)
    {
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            if (x == sx && y == sy)
                continue;

            prev[x][y] = glm::ivec2(-1, -1);    // Undefined
            dist[x][y] = INT_MAX;               // Mark as infinity, since we don't know the cost yet
            map[x][y]->reset_touch();           // Reset the touched flag, for calculating next shortest path to next target
        }
    }

    // Possible x, y directions. Up down, left and right
    int dx[4] = { 1, -1, 0, 0 };
    int dy[4] = { 0, 0, 1, -1 };
    while (!pq.empty())
    {
        Node curr = pq.top();
        pq.pop();

        // If we are on target
        if (curr.x == tx && curr.y == ty)
            break;

        // Check if we have shorter path cost
        if (curr.cost > dist[curr.x][curr.y])
            continue;

        map[curr.x][curr.y]->touch();

        // Go through all possible neighbours of current Tile/Node
        for (int nxy = 0; nxy < 4; nxy++)
        {
            int neighbour_x = curr.x + dx[nxy];
            int neighbour_y = curr.y + dy[nxy];

            // X map boundry check
            if (neighbour_x < 0 || neighbour_x >= MAP_WIDTH)
                continue;

            // Y map boundry check
            if (neighbour_y < 0 || neighbour_y >= MAP_HEIGHT)
                continue;

            int neighbour_cost = curr.cost + map[neighbour_x][neighbour_y]->get_movement_cost();
            if (neighbour_cost < dist[neighbour_x][neighbour_y])
            {
                prev[neighbour_x][neighbour_y] = glm::ivec2(curr.x, curr.y);
                dist[neighbour_x][neighbour_y] = neighbour_cost;
                pq.push(Node(neighbour_x, neighbour_y, neighbour_cost));
            }
        }
    }

    // No possible path
    if (dist[tx][ty] == INT_MAX)
        return -1;

    return dist[tx][ty];
}

int PathHandler::a_star(glm::ivec2 start, glm::ivec2 target)
{
    std::priority_queue<Node, std::vector<Node>, CompareTentativeScore> pq;

    int sx = start.x;
    int sy = start.y;
    int tx = target.x;
    int ty = target.y;

    // First start from "start" position
    dist[sx][sy] = 0;
    int start_ts = taxicap_distance(start, target);
    pq.push(Node(sx, sy, 0, start_ts));

    // Initilition of nodes
    for (int x = 0; x < MAP_WIDTH; x++)
    {
        for (int y = 0; y < MAP_HEIGHT; y++)
        {
            if (x == sx && y == sy)
                continue;

            prev[x][y] = glm::ivec2(-1, -1);    // Undefined
            dist[x][y] = INT_MAX;               // Mark as infinity, since we don't know the cost yet
            map[x][y]->reset_touch();           // Reset the touched flag, for calculating next shortest path to next target
        }
    }

    // Possible x, y directions. Up down, left and right
    int dx[4] = { 1, -1, 0, 0 };
    int dy[4] = { 0, 0, 1, -1 };
    while (!pq.empty())
    {
        Node curr = pq.top();
        pq.pop();

        // If we are on target
        if (curr.x == tx && curr.y == ty)
            break;

        // Check if we have shorter path cost
        if (curr.cost > dist[curr.x][curr.y])
            continue;

        map[curr.x][curr.y]->touch();

        // Go through all possible neighbours of current Tile/Node
        for (int nxy = 0; nxy < 4; nxy++)
        {
            int neighbour_x = curr.x + dx[nxy];
            int neighbour_y = curr.y + dy[nxy];

            // X map boundry check
            if (neighbour_x < 0 || neighbour_x >= MAP_WIDTH)
                continue;

            // Y map boundry check
            if (neighbour_y < 0 || neighbour_y >= MAP_HEIGHT)
                continue;

            int neighbour_cost = curr.cost + map[neighbour_x][neighbour_y]->get_movement_cost();
            int tentative_score = neighbour_cost + taxicap_distance(glm::ivec2(neighbour_x, neighbour_y), target);
            if (neighbour_cost < dist[neighbour_x][neighbour_y])
            {
                prev[neighbour_x][neighbour_y] = glm::ivec2(curr.x, curr.y);
                dist[neighbour_x][neighbour_y] = neighbour_cost;
                pq.push(Node(neighbour_x, neighbour_y, neighbour_cost, tentative_score));
            }
        }
    }

    // No possible path
    if (dist[tx][ty] == INT_MAX)
        return -1;

    return dist[tx][ty];
}

int PathHandler::taxicap_distance(glm::ivec2 left, glm::ivec2 right)
{
    return std::abs(left.x - right.x) + std::abs(left.y - right.y);
}

void PathHandler::rebuild_shortest_path(glm::ivec2 start, glm::ivec2 target)
{
    int sx = start.x;
    int sy = start.y;
    int tx = target.x;
    int ty = target.y;

    int x = tx;
    int y = ty;

    map[sx][sy]->set_path();
    while (!(x == sx && y == sy))
    {
        if (prev[x][y].x == -1 || prev[x][y].y == -1)
            break;

        map[x][y]->set_path();
        glm::ivec2 p = prev[x][y];
        x = p.x;
        y = p.y;
    }
}
