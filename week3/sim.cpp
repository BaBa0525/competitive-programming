#include <iostream>
#include <iterator>
#include <list>
#include <string>

class Editor {
public:
  Editor() : cursor{buffer.end()} {};

  void print() {
    std::cout << std::string(buffer.begin(), buffer.end()) << "\n";
  }

  void keypress(char c) {
    switch (c) {
    case '<':
      if (cursor == buffer.begin()) {
        break;
      }
      buffer.erase(std::prev(cursor));
      break;
    case '[':
      cursor = buffer.begin();
      break;
    case ']':
      cursor = buffer.end();
      break;
    default:
      buffer.insert(cursor, c);
    }
  }

  std::list<char> buffer;
  std::list<char>::iterator cursor;
};

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  int n;
  std::cin >> n;
  std::cin.get();

  while (n--) {
    std::string s;
    std::getline(std::cin, s);

    Editor e;
    for (auto &c : s) {
      e.keypress(c);
    }

    e.print();
  }

  return 0;
}
