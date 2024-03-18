#include <bitset>
#include <iostream>
#include <utility>
#include <vector>

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  int n;
  std::cin >> n;

  std::bitset<26> map;

  for (int i = 0; i < n; i++) {
    char c;
    std::cin >> c;

    if (c == 'T') {
      map[i] = true;
      continue;
    }
    map[i] = false;
  }

  char c;
  std::vector<bool> stack;

  auto pop_two = [&stack]() {
    bool a = stack.back();
    stack.pop_back();
    bool b = stack.back();
    stack.pop_back();

    return std::pair(a, b);
  };

  while (std::cin >> c) {
    if (c >= 'A' && c <= 'Z') {
      stack.push_back(map[c - 'A']);
      continue;
    }

    switch (c) {
    case '*': {
      auto [a, b] = pop_two();
      stack.push_back(a && b);
      break;
    }
    case '+': {
      auto [a, b] = pop_two();
      stack.push_back(a || b);
      break;
    }
    case '-': {
      stack.back().flip();
      break;
    }
    default:
      break;
    }
  }

  std::cout << (stack.back() ? "T\n" : "F\n");

  return 0;
}
