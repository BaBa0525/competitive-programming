#include <algorithm>
#include <iostream>
#include <limits>

int main() {
  int n;
  std::cin >> n;

  int min_h = std::numeric_limits<int>::max(), max_dist = 0;
  int max_h = 0;

  for (int i = 0; i < n; i++) {
    int h;
    std::cin >> h;

    if (h > max_h) {
      max_dist = std::max(max_dist, max_h - min_h);
      min_h = std::numeric_limits<int>::max();
      max_h = h;

      continue;
    }

    if (h < min_h) {
      min_h = h;
      continue;
    }

    max_dist = std::max(max_dist, h - min_h);
  }

  std::cout << max_dist << "\n";

  return 0;
}
