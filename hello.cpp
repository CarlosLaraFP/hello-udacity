#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::string;
using std::vector;

// g++ -std=c++17 hello.cpp -o hello
int main() {
  vector<string> colors{"Blue", "Green", "Red", "Silver"};

  // Iterating as immutable references
  for (string const &color : colors) {
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

  vector<vector<int>> board = {
    {10, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 20}
 };

 vector<int> &first = board.front();
 vector<int> &last = board.back();

 cout << "First element: " << first[0] << "\n";
 cout << "Last element: " << last[last.size() - 1] << "\n";

 auto count = 0;

 for (auto const &file : board) {
  for (auto const &tile : file) {
    count += 1;
  }
 }

 cout << "There are " << count << " tiles in the board.\n";
}
