#include <cstdint>
#include <iostream>
#include <vector>

struct FenwickTree {
  std::vector<int64_t> arr;
  FenwickTree(size_t N) : arr(N + 1, 0) {}

  void modify(int x, int val) {
    /* x += (x & -x) => go to closest right ancestor */
    for (; x < arr.size(); x += (x & -x)) {
      arr[x] += val;
    }
  }

  int64_t query(int x) {
    int64_t result{0};

    for (; x > 0; x -= (x & -x)) {
      result += arr[x];
    }

    return result;
  }

  int64_t query(int left, int right) { return query(right) - query(left - 1); }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  size_t n;
  std::cin >> n;

  FenwickTree num_count{n}, two_reversed{n};

  int64_t ans{0};
  for (size_t i{0}; i < n; i++) {
    int num;
    std::cin >> num;

    num_count.modify(num, 1);
    ans += two_reversed.query(num + 1, n);

    two_reversed.modify(num, num_count.query(num + 1, n));
  }

  std::cout << ans << '\n';

  return 0;
}
