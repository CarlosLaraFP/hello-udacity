#include <iostream>
#include <string>
#include <vector>

// g++ -std=c++17 hello.cpp -o hello
int main() {
  std::vector<std::string> colors{"Blue", "Green", "Red"};

  // Iterating as immutable references
  for (std::string const &color : colors) {
    std::cout << "Hello " << color << "!\n";
  }
}
