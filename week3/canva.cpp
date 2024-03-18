#include <iostream>
#include <queue>
#include <vector>

using u64 = unsigned long long;

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  int n_cases;
  std::cin >> n_cases;

  while (n_cases--) {
    int n_canvas;
    std::cin >> n_canvas;

    std::priority_queue<u64, std::vector<u64>, std::greater<u64>> areas;

    for (int i = 0; i < n_canvas; i++) {
      int a;
      std::cin >> a;
      areas.push(a);
    }

    auto get_min_and_pop = [&areas]() {
      u64 a = areas.top();
      areas.pop();
      return a;
    };

    u64 answer = 0;
    while (areas.size() != 1) {
      u64 a = get_min_and_pop();
      a += get_min_and_pop();

      areas.push(a);
      answer += a;
    }

    std::cout << answer << '\n';
  }

  return 0;
}
