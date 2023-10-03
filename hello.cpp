/*
  #include <filename> is typically used for system header files. 
  The preprocessor searches for the file in the standard system directories.

  #include "filename" is typically used for user-defined header files. 
  The preprocessor first searches for the file in the same directory as the file that contains the #include directive. 
  If it doesn't find the file there, it then searches the standard system directories.
*/
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

#include "functions.h"
#include "types.h"
#include "planning.h"
#include "date.hpp"

using std::cout;
using std::string;
using std::vector;


// g++ -std=c++17 hello.cpp -o hello && ./hello
/*
  When you compile a project with g++, g++ actually performs several distinct tasks:

  The preprocessor runs and executes any statement beginning with a hash symbol: #, such as #include statements. This ensures all code is in the correct location and ready to compile.
  Each file in the source code is compiled into an "object file" (a .o file). Object files are platform-specific machine code that will be used to create an executable.
  The object files are "linked" together to make a single executable. In the examples you have seen so far, this executable is a.out, but you can specify whatever name you want.

  CMakeLists.txt files can be used to specify the locations of necessary packages, set build flags and environment variables, specify build target names and locations, and other actions.
  In general, CMake only needs to be run once for a project, unless you are changing build options (e.g. using different build flags or changing where you store your files).
  Make will be able to keep track of which files have changed and compile only those that need to be compiled before building.
  Note: If you do re-run CMake, or if you are having problems with your build, it can be helpful to delete your build directory and start from scratch. Otherwise, some environment variables may not be reset correctly.

  mkdir build
  cd build
  cmake ..
  make
*/
int main() {
  /*
    An array is a C++ container much like a vector, although without the ability to change size after initialization.
  */
  vector<string> colors{"Blue", "Green", "Red", "Silver"};

  // Iterating as immutable references
  for (const string& color : colors) {
    cout << "Hello " << color << "!\n";
  }

  vector<int> v_1{0, 1, 2};
  auto v_2 = {3, 4, 5};
  vector<int> v_3;
  v_3 = {6};
  cout << "Everything worked!" << "\n";

  // Creating a 2D vector.
  vector<vector<int>> v {{1,2}, {3,4}};
  cout << "Great! A 2D vector has been created." << "\n";

  auto numbers = {6, 7, 8, 9};

  vector<vector<int>> grid = {
    {0, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0}
  };

  cout << "Random element: " << grid[0][1] << "\n";

  vector<int> &first = grid.front();
  vector<int> &last = grid.back();

  cout << "First element: " << first[0] << "\n";
  cout << "Last element: " << last[last.size() - 1] << "\n";

  auto count = 0;

  for (const auto& file : grid) {
    for (const auto& tile : file) {
      count += 1;
    }
  }

  cout << "There are " << count << " tiles in the grid.\n";

  // Wow. Be careful.
  //cout << "Invalid element: " << first[20] << "\n";

  for (auto i = 0; i < 5; i++) {
    cout << i << "\n";
  }

  auto i = 1;

  // Post-increment assigns i to c and then increments i.
  auto c = i++;

  cout << "Post-increment example:" << "\n";
  cout << "The value of c is: " << c << "\n";
  cout << "The value of i is: " << i << "\n";
  cout << "\n";

  // Reset i to 1.
  i = 1;

  // Pre-increment increments i, then assigns to c.
  c = ++i;

  cout << "Pre-increment example:" << "\n";
  cout << "The value of c is: " << c << "\n";
  cout << "The value of i is: " << i << "\n";
  cout << "\n";

  // Decrement i;
  i--;
  cout << "Decrement example:" << "\n";
  cout << "The value of i is: " << i << "\n";

  for (auto i = -3; i < 11; i++) {
    cout << i << " ";
  }
  cout << "\n";

  vector<int> fibonacci = {1, 1, 2, 3, 5, 8};
  /*
    for (int i: fibonacci) {
        cout << i << "\n";
    }

    This loop is making a copy of each element in the vector. 
    The variable i is a new int that gets assigned the value of the current element in the loop. 
    This means that if you modify i inside the loop, it does not affect the original value stored in the vector.
  */

  /*
    This loop does not make a copy of each element in the container. 
    Instead, it uses a reference to directly access each element of the container. 
    The const qualifier indicates that the referenced values cannot be changed within the loop. 
    This approach is more efficient than the first loop when dealing with large data or non-primitive 
    data types (such as classes or structs) because it avoids unnecessary copying. 
    However, in your example, you're dealing with a vector of integers, so the efficiency difference would likely be negligible.
  */
  for (const int& i : fibonacci) {
    cout << i << " ";
  }
  cout << "\n";

  // Write a double range-based for loop that prints all of the entries of the 2D vector
  vector<vector<int>> matrix {
    {1, 2}, 
    {3, 4}, 
    {5, 6}
  };

  DisplayMatrix(matrix);

  int result = Sum(fibonacci);
  assert(result == 20);

  vector<float> decimals = {1.1, 2.2, 3.3, 3.4};
  float sum = Sum(decimals);
  assert(sum == 10.0);

  DisplayMatrix(grid);

  auto j = 1;

  while (j <= 10) {
    if (j % 2 == 0) {
      cout << j << "\n";
    }
    j++;
  }

  enum class Direction {kUp, kDown, kLeft, kRight};

  Direction a = Direction::kUp;

  switch (a) {
    case Direction::kUp : cout << "Going up!" << "\n";
      break;
    case Direction::kDown : cout << "Going down!" << "\n";
      break;
    case Direction::kLeft : cout << "Going left!" << "\n";
      break;
    case Direction::kRight : cout << "Going right!" << "\n";
      break;
  }

  assert(ReadBoardFile("../files/2.board").size() == 0);

  /*
    A* motion planning search algorithm
  */
  auto board = ReadBoardFile("../files/1.board");
  DisplayBoard(board);

  auto start = Coordinate {0, 0};
  auto goal = Coordinate {4, 5};

  auto solution = Search(board, start, goal);

  DisplayBoard(solution);

  Date date{1, 12, 2000};
  assert(date.Day() == 1);
  assert(date.Month() <= 12);
  assert(date.Year() == 2000);

  Student student{"Albert", 9, 4.0};
  assert(student.Name() == "Albert");
  assert(student.Grade() == 9);
  assert(student.GPA() == 4.0);
  
  try { 
      student.setGrade(19); 
  } 
  catch (const std::invalid_argument& e) { 
      std::cerr << "Caught an invalid_argument exception: " << e.what() << std::endl;
  }

  Scooter scooter {4, "blue sky", true};
  scooter.Print();

  Square square {4};
  Rectangle rectangle {square};
  assert(rectangle.Area() == 16); 
}
