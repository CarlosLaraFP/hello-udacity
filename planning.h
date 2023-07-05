#ifndef PLANNING_H
#define PLANNING_H

#include <iostream>
#include <vector>
#include <algorithm>  // for sort

#include "types.h"
#include "functions.h"

using std::cout;
using std::vector;
using std::sort;

/*
  The code for the A* search algorithm is composed of the following functions:

  CellSort() - sorts the open list according to the sum of h + g
  ExpandNeighbors() - loops through the current node's neighbors and calls appropriate functions to add neighbors to the open list
  CheckValidCell() - ensures that the potential neighbor coordinates are on the grid and that the cell is open
  Heuristic() - computes the distance to the goal
  AddToOpen() - adds the node to the open list and marks the grid cell as closed
  Helper functions
*/

int Heuristic(const int& x_1, const int& y_1, const int& x_2, const int& y_2) {
  /*
    The parameters represent two pairs of 2D coordinates.
    Returns an int which is the Manhattan Distance from one coordinate to the other:
    |x_2 - x_1| + |y_2 - y_1|
  */
  return abs(x_2 - x_1) + abs(y_2 - y_1);
}

void AddToOpen(const Node& node, vector<Node>& open_nodes, vector<vector<TileState>>& grid) {
  /*
    Adds an immutable Node reference to a mutable vector reference (list of open nodes).
    Modifies the mutable reference to the grid for the node just visited, marking it as closed.
  */
  open_nodes.push_back(node);
  grid[node.x][node.y] = TileState::Closed;
}

bool Compare(const Node& node_a, const Node& node_b) {
    auto f_a = node_a.g + node_a.h;
    auto f_b = node_b.g + node_b.h;
    return f_a > f_b;
}

/**
 * Sort the two-dimensional vector of ints in descending order.
 */
void CellSort(vector<Node>* v) {
  /*
    The arrow operators (->) are used here because v is a pointer to a vector, so we need to dereference it to access its members.
    The first two parameters are iterators to the beginning and the end of the vector.
    This code is a bit simpler and safer than the version with the pointer because you don't need to use 
    the -> operator to access the vector's methods, and safer because you can't accidentally pass a nullptr.
  */
  sort(v->begin(), v->end(), Compare);
}

void ExpandNeighbors() {

}

vector<vector<TileState>> Search(vector<vector<TileState>>& grid, const int start[2], const int goal[2]) {
  /*
  */
  if (grid.empty()) {
    cout << "No path found.\n";
    return grid;
  }

  vector<Node> open_nodes;

  auto x_1 = start[0];
  auto y_1 = start[1];
  auto x_2 = goal[0];
  auto y_2 = goal[1];

  auto first_node = Node {
    x_1,
    y_1,
    0,
    Heuristic(x_1, y_1, x_2, y_2)
  };

  AddToOpen(first_node, open_nodes, grid);

  while (!open_nodes.empty()) {
    // Sort vector<Node> by ascending f value (g + h)
    CellSort(&open_nodes);

    // Get the last node because the vector with the smallest f value is closest to the goal
    Node closest = open_nodes.back();

    // Mark the path for displaying it at the end
    grid[closest.x][closest.y] = TileState::Path;

    if (Heuristic(closest.x, closest.y, x_2, y_2) == 0) {
      return grid;
    }

    ExpandNeighbors();
  }

  return grid;
}

#endif // PLANNING_H