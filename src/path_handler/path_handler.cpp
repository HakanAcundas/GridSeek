#include <iostream>
#include "path_handler.hpp"

PathHandler::PathHandler()
{

}

// Pseudocode: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm#Pseudocode
int PathHandler::dijkstra(std::array<std::array<std::unique_ptr<Tile>, MAP_HEIGHT>, MAP_WIDTH>& map,
    glm::ivec2 start, glm::ivec2 target)
{
    std::cout << "Dijkstra tries to find shortest path.\n";
    // Clear priority queue
    pq = std::priority_queue<Node, std::vector<Node>, CompareCost>();
    
    int sx = start.x;
    int sy = start.y;
    int tx = target.x;
    int ty = target.y;
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
            map[x][y]->reset_path();
        }
    }

    // Possible x, y directions
    int dx[8] = { 1, -1, 0, 0, 1, 1, -1, -1};
    int dy[8] = { 0, 0, 1, -1, 1, -1, 1, -1};
    while (!pq.empty())
    {
        Node curr = pq.top();
        pq.pop();

        // If we are on target
        if (curr.x == tx && curr.y == ty)
            break;

        // Check if we have shorter path cost
        if (curr.cost > dist[curr.x][curr.y] || map[curr.x][curr.y]->is_touched())
            continue;

        map[curr.x][curr.y]->touch();

        // Go through all possible neighbours of current Tile/Node
        for (int nxy = 0; nxy < 8; nxy++)
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

    rebuild_shortest_path(map, start, target);

    return dist[tx][ty];
}

void PathHandler::rebuild_shortest_path(std::array<std::array<std::unique_ptr<Tile>, MAP_HEIGHT>, MAP_WIDTH>& map,
    glm::ivec2 start, glm::ivec2 target)
{
    std::cout << "Building the shortest path.\n";
    int sx = start.x;
    int sy = start.y;
    int tx = target.x;
    int ty = target.y;

    int x = tx;
    int y = ty;

    while (!(x == sx && y == sy))
    {
        if (prev[x][y].x == -1)
            break;

        map[x][y]->set_path();

        glm::ivec2 p = prev[x][y];
        x = p.x;
        y = p.y;
    }

    map[sx][sy]->set_path();
}
