#include <cstddef>
#include <iostream>

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  int n;
  std::cin >> n;

  for (int i = 0; i < n; i++) {
    std::size_t candidate = 0;
    for (int j = 0; j < n; j++) {
      int a;
      std::cin >> a;
      candidate |= a;
    }
    std::cout << candidate << ' ';
  }

  std::cout << "\n";

  return 0;
}
