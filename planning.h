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

// directional deltas
const int delta [4][2] = {
  {-1, 0}, 
  {0, -1}, 
  {1, 0}, 
  {0, 1}
};

int Distance(const Coordinate& a, const Coordinate& b) {
  /*
    The parameters represent two pairs of 2D coordinates.
    Returns an int which is the Manhattan Distance from one coordinate to the other:
    |x_2 - x_1| + |y_2 - y_1|
  */
  return abs(b.x - a.x) + abs(b.y - a.y);
}

void AddToOpen(const Node& node, vector<Node>& open_nodes, vector<vector<TileState>>& grid) {
  /*
    Adds an immutable Node reference to a mutable vector reference (list of open nodes).
    Modifies the mutable reference to the grid for the node just visited, marking it as closed.
  */
  open_nodes.push_back(node);
  grid[node.c.x][node.c.y] = TileState::Closed;
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

bool CheckValidCell(const Coordinate& c, const vector<vector<TileState>>& grid) {
    auto valid_row = c.x >= 0 && c.x < grid.size();
    auto valid_column = c.y >= 0 && c.y < grid[0].size();
    // if out of bounds, buffer overflow => segfault
    if (valid_row && valid_column) {
      return grid[c.x][c.y] == TileState::Free;
    }
    return false;
}

void ExpandNeighbors(const Node& current_node, vector<Node>& open_nodes, vector<vector<TileState>>& grid, const Coordinate& goal) {
  // Iterating through constant array defined at the top
  for (auto& d : delta) {
    auto current_coordinate = Coordinate {
      current_node.c.x + d[0], 
      current_node.c.y + d[1]
    };

    if (CheckValidCell(current_coordinate, grid)) {
      auto neighbor = Node {
        current_coordinate,
        current_node.g + 1,
        Distance(current_coordinate, goal)
      };

      AddToOpen(neighbor, open_nodes, grid);
    }
  }
}

vector<vector<TileState>> Search(vector<vector<TileState>>& grid, const Coordinate& start, const Coordinate& goal) {
  /*
  */
  if (grid.empty()) {
    cout << "Please provide a non-empty grid.\n";
    return grid;
  }

  vector<Node> open_nodes;

  auto first_node = Node {
    start,
    0,
    Distance(start, goal)
  };

  AddToOpen(first_node, open_nodes, grid);

  while (!open_nodes.empty()) {
    // Sort vector<Node> by ascending f value (g + h)
    /*
      A C++ pointer is a variable that stores the memory address of an object in your program.
      Each variable in a program stores its contents in the computer's memory, and each chunk of the memory has an address number. 
      For a given variable, the memory address can be accessed using an ampersand in front of the variable.
    */
    CellSort(&open_nodes);

    // Get the last node because the vector with the smallest f value is closest to the goal
    Node closest = open_nodes.back();
    // Since we copied the node into a separate variable, we remove the original one from the vector of open nodes
    open_nodes.pop_back();

    // Mark the path for displaying it at the end
    grid[closest.c.x][closest.c.y] = TileState::Path;

    if (Distance(closest.c, goal) == 0) {
      grid[start.x][start.y] = TileState::Start;
      grid[goal.x][goal.y] = TileState::Finish;
      return grid;
    }

    ExpandNeighbors(closest, open_nodes, grid, goal);
  }

  cout << "No path found.\n";
  return grid;
}

/*
  In A Tour of C++, Bjarne Stroustrup writes:

  C++ supports two notions of immutability:

  const: meaning roughly " I promise not to change this value."...The compiler enforces the promise made by const....

  constexpr: meaning roughly "to be evaluated at compile time." This is used primarily to specify constants...
*/

#endif // PLANNING_H