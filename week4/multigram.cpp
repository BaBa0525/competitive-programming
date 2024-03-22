#include <functional>
#include <ios>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  std::string s;
  std::cin >> s;

  for (int i = 1; i <= (s.size() / 2); i++) {
    if (s.size() % i != 0) {
      continue;
    }

    int num_seg = s.size() / i;
    std::vector<std::vector<int>> freq(num_seg, std::vector<int>(26, 0));
    for (int j = 0; j < s.size(); j++) {
      freq[j / i][s[j] - 'a']++;
    }

    std::function<bool()> check = [&]() {
      for (int j = 1; j < num_seg; j++) {
        if (freq[0] != freq[j]) {
          return false;
        }
      }
      return true;
    };

    if (check()) {
      std::string_view sv{s};
      std::cout << sv.substr(0, i) << "\n";
      return 0;
    }
  }

  std::cout << -1 << "\n";

  return 0;
}
