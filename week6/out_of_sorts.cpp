#include <cstddef>
#include <iostream>
#include <vector>

using i64 = long long;

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  i64 n, m, a, c;
  std::cin >> n >> m >> a >> c;

  std::vector<i64> arr(n + 1);
  std::cin >> arr[0];
  for (int i{1}; i < arr.size(); i++) {
    arr[i] = (a * arr[i - 1] + c) % m;
  }

  int ans{0};
  for (int i{1}; i < arr.size(); i++) {
    std::size_t left{1}, right{arr.size() - 1};

    while (left <= right) {
      int mid = (left + right) / 2;

      if (arr[mid] == arr[i]) {
        ans++;
        break;
      }

      if (arr[i] < arr[mid]) {
        right = mid - 1;
      }

      if (arr[mid] < arr[i]) {
        left = mid + 1;
      }
    }
  }

  std::cout << ans << '\n';

  return 0;
}
