#ifndef PLANNING_H
#define PLANNING_H

#include <iostream>
#include <vector>
#include "types.h"
#include "functions.h"

using std::cout;
using std::vector;

/*
  The code for the A* search algorithm is composed of the following functions:

  CellSort() - sorts the open list according to the sum of h + g
  ExpandNeighbors() - loops through the current node's neighbors and calls appropriate functions to add neighbors to the open list
  CheckValidCell() - ensures that the potential neighbor coordinates are on the grid and that the cell is open
  Heuristic() - computes the distance to the goal
  AddToOpen() - adds the node to the open list and marks the grid cell as closed
  Helper functions
*/

vector<vector<TileState>> Search(const vector<vector<TileState>>& board, const int start[2], const int goal[2]) {
  /*
  */
  vector<vector<TileState>> result;
  cout << "No path found.\n";
  return result;
}

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
  */
  open_nodes.push_back(node);
  grid[node.x][node.y] = TileState::Closed;
}

#endif // PLANNING_H