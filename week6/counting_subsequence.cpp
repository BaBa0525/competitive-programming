#include <iostream>
#include <map>

using i64 = long long;

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  int t;
  std::cin >> t;

  while (t--) {
    int n;
    std::cin >> n;

    std::map<int, int> prefix_count;
    prefix_count[0] = 1;  // self
    i64 prefix{0}, ans{0};

    for (int i{0}; i < n; i++) {
      int a;
      std::cin >> a;
      prefix += a;
      prefix_count[prefix] += 1;

      auto it = prefix_count.find(prefix - 47);
      if (it == prefix_count.end()) continue;
      ans += it->second;
    }

    std::cout << ans << '\n';
  }

  return 0;
}
