#include <cstdint>
#include <iostream>
#include <vector>

int64_t find_origin(int64_t target, int64_t fib_idx,
                    const std::vector<int64_t> &fib) {
  if (fib_idx <= 2) return fib_idx;

  if (fib_idx > fib.size() or target <= fib[fib_idx - 2]) {
    return find_origin(target, fib_idx - 2, fib);
  }

  return find_origin(target - fib[fib_idx - 2], fib_idx - 1, fib);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int64_t n, k;
  std::cin >> n >> k;

  std::vector<int64_t> fib(3, 1);
  for (int i{3}; fib.back() <= 1e18; i++) {
    fib.push_back(fib[n - 1] + fib[i - 2]);
  }

  int origin = find_origin(k, n, fib);

  if (origin == 1)
    std::cout << "N\n";
  else
    std::cout << "A\n";

  return 0;
}
