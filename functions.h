/*
  The FUNCTIONS_H is known as an "include guard". 
  Its role is to prevent the contents of the header file from being processed more than once by the preprocessor.

  If you include a header file in multiple places within your project, and that header file doesn't have an include guard, 
  then its contents will be copied into every file that includes it. This can lead to issues like redefinition errors.

  The way the include guard works is like this:

  #ifndef FUNCTIONS_H: This is a preprocessor directive that checks if FUNCTIONS_H has not been defined yet. 
  If it hasn't, then the preprocessor continues to the next line. If it has, the preprocessor skips to the line after #endif.

  #define FUNCTIONS_H: This line defines FUNCTIONS_H. The next time the preprocessor encounters #ifndef FUNCTIONS_H, it will skip to the line after #endif.

  #endif: This marks the end of the block of code that is guarded by #ifndef FUNCTIONS_H.

  The choice of FUNCTIONS_H is arbitrary; you could use any valid identifier. However, it is common practice 
  to use a name related to the file name, all in uppercase, to make it clear and easy to avoid conflicts. 
  If you had another file called utilities.h, you might use UTILITIES_H as the include guard in that file.
*/
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <vector>
#include <numeric>
#include <type_traits>
#include <fstream>
#include <sstream>

#include "types.h"

using std::cout;
using std::vector;
using std::accumulate;
using std::string;
using std::ifstream;
using std::istringstream;


vector<TileState> ParseLine(const string& line) {
  int n;
  char c;
  vector<TileState> row;
  istringstream stream(line);

  // The extraction operator will read until whitespace is reached or until the stream fails
  while (stream >> n >> c) {
    if (n == 0) {
      row.push_back(TileState::Free);
    }
    else {
      row.push_back(TileState::Blocked);
    }
  }

  return row;
}

vector<vector<TileState>> ReadBoardFile(const string& file_path) {
  /*
    Parse string lines from the board and store the ints in a vector using istringstream and push_back
  */
  ifstream file(file_path);
  vector<vector<TileState>> board;

  if (file) {
    cout << "Successfully read " << file_path << " into an input file stream object.\n";
    string line;

    while (getline(file, line)) {
      auto row = ParseLine(line);
      board.push_back(row);
    }
  }
  else {
    cout << "Path " << file_path << " does not exist or could not be found.\n";
  }

  return board;
}

string TileToString(const TileState& tile) {
    switch (tile) {
        case TileState::Blocked: return "⛰️";
        case TileState::Closed: return "X";
        case TileState::Path: return "P";
        default: return "0"; // TileState::Free
    }
}

void DisplayBoard(const vector<vector<TileState>>& board) {
  for (const auto& row : board) {
    for (const auto& tile : row) {
      cout << TileToString(tile) << " ";
    }
    cout << "\n";
  }
}

template <typename T>
void DisplayMatrix(const vector<vector<T>>& matrix) {
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
}

template <typename T>
T Sum(const vector<T>& elements) {
  /*
    This function should, at a monimum, accept a vector of ints and return their sum.
    Enforces compile-time checking and ensures only numeric types are used.

    std::is_arithmetic<T>::value will return true if T is a numeric type (integral or floating point), and false otherwise.
    std::accumulate from the standard library is used to sum up (accumulate) the values of all the elements within a range specified by two iterators.

    data.begin(): This returns an iterator pointing to the first element of the data vector. 
    In C++, the begin() function gives an iterator pointing to the start of the container.
    
    data.end(): This returns an iterator pointing one position past the last element of the data vector. 
    In C++, the end() function returns an iterator to the "end" of the container, which is one past the last element, rather than the last element itself. 
    This follows a common idiom in C++ of specifying ranges as [first, last) — i.e., including the first element but excluding the last.

    static_cast<T>(0): This is casting the integer 0 to the type T. The static_cast<T> is a compile-time cast that can perform conversions between types. 
    It's needed here to ensure that the initial value has the correct type.

    For example, if you're accumulating a vector of double, you'd want the initial value to be a double (i.e., 0.0) and not an int (0), because using an 
    integer could potentially lead to integer (truncating) division instead of floating-point division when the accumulate function is performing its calculations.

    So, the final line means "sum up all the values in the vector data, starting with an initial value of 0 of the appropriate type, and return the sum."
  */
  static_assert(std::is_arithmetic<T>::value, "Vector must be of a numeric type.");

  return std::accumulate(elements.begin(), elements.end(), static_cast<T>(0));
}

/*
  The use of static_assert along with std::is_arithmetic does not incur a runtime performance penalty. This is because these checks occur at compile-time, not at runtime.

  In C++, templates and type traits like std::is_arithmetic are evaluated by the compiler at compile time. 
  They generate specific code for each type that's used as a template argument, just as if you had written separate functions or classes for each type.

  static_assert also does its work at compile time. If its condition is false, it causes a compile error; if the condition is true, it has no effect on the generated code. 
  It does not produce any instructions that would slow down the program at runtime.

  So you can use these features to make your code more flexible and safe, without worrying about a performance cost. 
  They're part of what makes C++ a powerful language for high-performance programming.
*/

#endif // FUNCTIONS_H