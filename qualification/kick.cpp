#include <iostream>
#include <string>

int main() {
  std::string input;
  std::cin >> input;

  std::string target{"kick"};

  int total_kicks = 0;
  int next_match = 0;
  for (auto &c : input) {
    if (c == target[next_match]) {
      if (next_match != target.size() - 1) {
        next_match++;
      } else {
        next_match = 1;
        total_kicks++;
      }
      continue;
    }
    if (c == target[0]) {
      next_match = 1;
      continue;
    }
    next_match = 0;
  }

  std::cout << total_kicks << '\n';

  return 0;
}
