#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <utility>

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  int num_customers;

  while (std::cin >> num_customers && num_customers != 0) {
    std::cin.get(); // consume newline

    std::map<std::string, std::set<std::string>> history;
    while (num_customers--) {
      std::string line;
      std::getline(std::cin, line);

      std::stringstream ss(std::move(line));
      std::string name, food;
      ss >> name;

      while (ss >> food) {
        history[food].insert(name);
      }
    }

    for (auto &[food, customers] : history) {
      std::cout << food << ' ';
      for (auto &c : customers) {
        std::cout << c << ' ';
      }
      std::cout << '\n';
    }

    std::cout << '\n';
  }
}
