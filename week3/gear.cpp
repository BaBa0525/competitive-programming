#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  // number of gears on
  int n_crank, n_wheel, p;

  std::cin >> n_crank >> n_wheel >> p;

  std::vector<int> crank(n_crank);
  for (auto &c : crank) {
    std::cin >> c;
  }

  std::vector<int> wheel(n_wheel);
  for (auto &w : wheel) {
    std::cin >> w;
  }

  std::vector<double> cadence;
  cadence.reserve(n_crank * n_wheel);

  for (auto &c : crank) {
    for (auto &w : wheel) {
      cadence.push_back((double)c / w);
    }
  }

  std::sort(cadence.begin(), cadence.end());

  for (int i = 0; i < cadence.size() - 1; i++) {
    if (cadence[i + 1] / cadence[i] > (1 + p * 0.01)) {
      std::cout << "Time to change gears!\n";
      return 0;
    }
  }

  std::cout << "Ride on!\n";

  return 0;
}
