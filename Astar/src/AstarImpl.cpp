#include "AstarImpl.hpp"

Astar::Astar()
{
}

double Astar::heuristic(const Point& a, const Point& b)
{
  return std::sqrt(std::pow(a.first - b.first, 2) + std::pow(a.second - b.second, 2));
}

bool Astar::isValid(const Grid& grid, const Point& point)
{
  int x = point.first;
  int y = point.second;
  return (x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size() && grid[x][y] == 0);
}

std::vector<Astar::Point> Astar::reconstructPath(const std::vector<std::vector<Point>>& cameFrom, const Point& current)
{
  std::vector<Point> path;
  Point currentPoint = current;
  while (cameFrom[currentPoint.first][currentPoint.second] != currentPoint)
  {
    path.push_back(currentPoint);
    currentPoint = cameFrom[currentPoint.first][currentPoint.second];
  }
  path.push_back(currentPoint);
  std::reverse(path.begin(), path.end());
  return path;
}

std::vector<Astar::Point> Astar::findPath(const Grid& grid, const Point& start, const Point& end)
{
  std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openList;
  std::vector<std::vector<bool>> closedList(grid.size(), std::vector<bool>(grid[0].size(), false));
  std::vector<std::vector<Point>> cameFrom(grid.size(), std::vector<Point>(grid[0].size(), { -1, -1 }));

  openList.emplace(start, 0.0, heuristic(start, end), start);
  cameFrom[start.first][start.second] = start;

  while (!openList.empty())
  {
    Node current = openList.top();
    openList.pop();

    Point pos = current.position;
    if (pos == end)
    {
      return reconstructPath(cameFrom, end);
    }

    closedList[pos.first][pos.second] = true;

    std::vector<Point> neighbors = { { pos.first - 1, pos.second },
                                     { pos.first + 1, pos.second },
                                     { pos.first, pos.second - 1 },
                                     { pos.first, pos.second + 1 } };

    for (const auto& neighbor : neighbors)
    {
      if (isValid(grid, neighbor) && !closedList[neighbor.first][neighbor.second])
      {
        double tentativeG = current.g + 1.0;
        double h = heuristic(neighbor, end);
        Node neighborNode(neighbor, tentativeG, h, pos);

        if (cameFrom[neighbor.first][neighbor.second].first == -1 || tentativeG < neighborNode.g)
        {
          openList.push(neighborNode);
          cameFrom[neighbor.first][neighbor.second] = pos;
        }
      }
    }
  }

  return {};
}
