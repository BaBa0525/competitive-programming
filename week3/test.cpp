#include <cstddef>
#include <iostream>
#include <set>

class vec {
public:
  vec() = default;
  vec(const vec &other) { std::cout << "copy constructor" << std::endl; }
  vec(vec &&other) : data{other.data}, cap{other.cap}, size{other.size} {
    std::cout << "move constructor" << std::endl;
    other.data = nullptr;
    other.cap = 0;
    other.size = 0;
  }

private:
  int *data;
  std::size_t cap;
  std::size_t size;
};
int main() {

  int a = 3;
  int b = 5;

  std::cout << b / a << std::endl;

  return 0;
}
