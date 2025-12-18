#include "path_handler.hpp"

PathHandler::PathHandler()
{

}

int PathHandler::dijkstra(
    std::array<std::array<std::unique_ptr<Tile>, MAP_HEIGHT>, MAP_WIDTH>& map,
    glm::vec2 start,
    glm::vec2 target)
{
    // Clear priority queue
    pq = std::priority_queue<Node, std::vector<Node>, CompareCost>();

    // Initialize dist & prev
    for (int column = 0; column < MAP_HEIGHT; column++)
    {
        for (int row = 0; row < MAP_WIDTH; row++)
        {
            dist[row][column] = INT_MAX;
            prev[row][column] = glm::ivec2(-1, -1);
            map[row][column]->reset_path(); // important: clear old markings
        }
    }

    int sx = (int)start.x;
    int sy = (int)start.y;
    int tx = (int)target.x;
    int ty = (int)target.y;

    dist[sx][sy] = 0;
    pq.push(Node(sx, sy, 0));

    // Possible x and y directions
    static const int drow[4] = { 1, -1, 0, 0 };
    static const int dcol[4] = { 0, 0, 1, -1 };

    while (!pq.empty())
    {
        Node curr = pq.top();
        pq.pop();

        int x = curr.x;
        int y = curr.y;

        // Exit if we reach the target
        if (x == tx && y == ty)
            break;

        // Check if we have shorter path cost
        if (curr.cost > dist[x][y] || map[x][y]->is_touched())
            continue;

        map[x][y]->touch();

        for (int i = 0; i < 4; i++)
        {
            // Next x and y
            int nx = x + drow[i];
            int ny = y + dcol[i];

            // Boundry check for next tile, since we might exit from map
            if (nx < 0 || nx >= MAP_WIDTH || ny < 0 || ny >= MAP_HEIGHT)
                continue;

            int move_cost = map[nx][ny]->get_movement_cost();
            int new_cost = dist[x][y] + move_cost;

            if (new_cost < dist[nx][ny])
            {
                dist[nx][ny] = new_cost;
                prev[nx][ny] = glm::ivec2(x, y);
                pq.push(Node(nx, ny, new_cost));
            }
        }
    }

    // No path found
    if (dist[tx][ty] == INT_MAX)
        return -1;

    rebuild_shortest_path(start, target, map);

    return dist[tx][ty];
}

void PathHandler::rebuild_shortest_path(
    glm::vec2 start,
    glm::vec2 target,
    std::array<std::array<std::unique_ptr<Tile>, MAP_HEIGHT>, MAP_WIDTH>& map)
{
    int sx = (int)start.x;
    int sy = (int)start.y;
    int tx = (int)target.x;
    int ty = (int)target.y;

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

    map[sx][sy]->set_path(); // mark start if desired
}
