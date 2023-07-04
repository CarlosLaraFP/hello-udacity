#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <vector>

using std::cout;
using std::vector;


template <typename T>
void DisplayMatrix(vector<vector<T>> const &matrix) {
  /*
    Takes in a vector<vector<T>> prints its values in order.
    Iteration uses immutable references.
  */
  for (vector<T> const &v : matrix) {
    for (T const &e : v) {
      cout << e << " ";
    }
    cout << "\n";
  }
  cout << "\n";
}

#endif // FUNCTIONS_H