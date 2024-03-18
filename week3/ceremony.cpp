#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <set>
#include <vector>

void solve() {
  int n;
  std::cin >> n;
  std::vector<int> heights(n);

  for (auto &h : heights) {
    std::cin >> h;
  }

  std::sort(heights.begin(), heights.end(), std::greater<int>{});

  int answer = std::numeric_limits<int>::max();
  for (int i = 0; i < n; i++) {
    answer = std::min(answer, heights[i] + i);
  }

  std::cout << answer << '\n';
}

int main() {
  // for IO acceleration
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  std::multiset<int> building_height;

  int num_building;
  std::cin >> num_building;

  while (num_building--) {
    int h;
    std::cin >> h;
    building_height.insert(h);
  }

  // destory
  int horizon = 0, vertical = 0;

  while (!building_height.empty()) {
    auto highest = *building_height.rbegin() - horizon;

    if (highest > building_height.size()) {
      // destory building directly
      auto it = building_height.end();
      building_height.erase(--it);
      vertical++;
      continue;
    }

    horizon++;
    auto it = building_height.upper_bound(horizon);
    building_height.erase(building_height.begin(), it);
  }

  std::cout << horizon + vertical << "\n";

  return 0;
}
