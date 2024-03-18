#include <cstddef>
#include <expected>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

class Parser {
public:
  Parser() : has_error(false){};

  const Parser &operator<<(char c) {
    if (c == ' ') {
      return *this;
    }

    auto it = this->pair.find(c);
    if (it != this->pair.end()) {
      this->stack.push_back(it->second);
      return *this;
    }

    if (this->stack.empty() || this->stack.back() != c) {
      this->has_error = true;
      return *this;
    }
    this->stack.pop_back();

    return *this;
  }

  bool has_error;

private:
  std::vector<char> stack;
  std::map<char, char> pair;

  friend class ParserBuilder;
};

class ParserBuilder {
public:
  ParserBuilder() = default;

  ParserBuilder &add_pair(char key, char val) {
    this->parser.pair.insert_or_assign(key, val);

    return *this;
  }

  Parser build() { return std::move(this->parser); }

private:
  Parser parser;
};

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  int n;
  std::cin >> n;
  std::cin.get();

  auto p = ParserBuilder()
               .add_pair('[', ']')
               .add_pair('(', ')')
               .add_pair('{', '}')
               .build();

  for (std::size_t i = 0; i < n; i++) {
    char c = std::cin.get();
    p << c;
    if (p.has_error) {
      std::cout << c << ' ' << i << '\n';
      return 0;
    }
  }

  std::cout << "ok so far\n";
  return 0;
}
