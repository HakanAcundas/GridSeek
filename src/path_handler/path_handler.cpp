#include "path_handler.hpp"

PathHandler::PathHandler()
{

}

int PathHandler::minCost(std::array<std::array<std::shared_ptr<Tile>, MAP_WIDTH>, MAP_HEIGHT>& map, glm::vec2 start, glm::vec2 target)
{
    int sx = static_cast<int>(start.x);
    int sy = static_cast<int>(start.y);
    int tx = static_cast<int>(target.x);
    int ty = static_cast<int>(target.y);

    // Clear leftover PQ entries from previous calls
    pq = std::priority_queue<Node, std::vector<Node>, CompareCost>();

    // Store visited tiles to reset later
    std::vector<std::shared_ptr<Tile>> touched;

    // Start with initial node
    pq.push(Node(sx, sy, 0));
    map[sx][sy]->set_path();
    touched.push_back(map[sx][sy]);

    int result_cost = -1;

    // Dijkstra loop
    while (!pq.empty())
    {
        Node curr = pq.top();
        pq.pop();

        // If we are on target
        if (curr.row == tx && curr.col == ty)
        {
            result_cost = curr.cost;
            break;
        }

        // Movement directions. Up, down, right, left
        static const int drow[4] = { 1, -1, 0, 0 };
        static const int dcol[4] = { 0, 0, 1, -1 };

        for (int i = 0; i < 4; i++)
        {
            // Next row and next column
            int nrow = curr.row + drow[i];
            int ncol = curr.col + dcol[i];

            // Row bound check
            if (nrow < 0 || nrow >= MAP_WIDTH)
            {
                continue;
            }

            // Column bound check
            if (ncol < 0 || ncol >= MAP_HEIGHT)
            {
                continue;
            }

            // Get next tile
            auto& tile = map[nrow][ncol];

            // Check if tile is visited
            if (tile->is_path())
            {
                continue;
            }

            int move_cost = tile->get_movement_cost();

            pq.push(Node(nrow, ncol, curr.cost + move_cost));

            // Mark as visited
            tile->set_path();
            touched.push_back(tile);
        }
    }

    return result_cost;
}
