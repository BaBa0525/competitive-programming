#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n;
  std::cin >> n;
  std::vector<int> x(n), y(n);

  for (int i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }

  std::sort(x.begin(), x.end());
  std::sort(y.begin(), y.end());

  std::cout << x[(n - 1) / 2] << ' ' << y[(n - 1) / 2] << '\n';

  return 0;
}
