#include <cctype>
#include <charconv>
#include <cstddef>
#include <iostream>
#include <string>
#include <string_view>

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  std::string s;
  while (std::cin >> s) {

    for (std::size_t i = 0; i < s.size() - 1; i++) {
      if (s[i] != '0' || std::tolower(s[i + 1]) != 'x') {
        continue;
      }

      std::size_t j = i + 2;
      while (j < s.size() && std::isxdigit(s[j])) {
        j++;
      }

      if (j == i + 2) {
        continue;
      }

      std::string_view sv{&s[i], j - i};
      std::size_t result;

      // skip 0x
      std::from_chars(sv.data() + 2, sv.data() + sv.size(), result, 16);

      std::cout << sv << ' ' << result << '\n';

      i = j;
    }
  }

  return 0;
}
