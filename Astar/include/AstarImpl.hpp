#ifndef ASTARIMPL_HPP
#define ASTARIMPL_HPP

#include <algorithm>
#include <cmath>  // For std::abs, std::sqrt
#include <queue>
#include <utility>  // For std::pair
#include <vector>

class Astar
{
public:
  using Grid = std::vector<std::vector<int>>;
  using Point = std::pair<int, int>;

  Astar();
  std::vector<Point> findPath(const Grid& grid, const Point& start, const Point& end);

private:
  struct Node
  {
    Point position;
    double g;  // Cost from start to current node
    double h;  // Estimated cost from current node to end
    double f;  // Total cost (g + h)
    Point parent;

    Node(Point pos, double g_cost, double h_cost, Point par)
      : position(pos), g(g_cost), h(h_cost), f(g_cost + h_cost), parent(par)
    {
    }

    bool operator>(const Node& other) const
    {
      return f > other.f;  // For priority queue (min-heap)
    }
  };

  double heuristic(const Point& a, const Point& b);
  bool isValid(const Grid& grid, const Point& point);
  std::vector<Point> reconstructPath(const std::vector<std::vector<Point>>& cameFrom, const Point& current);
};

#endif  // ASTARIMPL_HPP
