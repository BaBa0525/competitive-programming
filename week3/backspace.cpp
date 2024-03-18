#include <iostream>
#include <string>

int main() {
  std::string output;
  char c;

  while (std::cin >> c) {
    if (c == '<') {
      output.pop_back();
      continue;
    }

    output.push_back(c);
  }

  std::cout << output << std::endl;

  return 0;
}
