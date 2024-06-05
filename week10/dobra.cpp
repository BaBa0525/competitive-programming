#include <cstdint>
#include <iostream>
#include <string>

bool is_vowel(char c) {
  static const std::string vowels{"AEIOU"};
  return vowels.find(c) != std::string::npos;
}

bool is_valid(std::string &s) {
  /* [vowel count, consonant count] */
  int seq_count[2]{};
  bool has_l{false};

  for (auto c : s) {
    int index{is_vowel(c) ? 0 : 1};
    seq_count[index]++;
    seq_count[index ^ 1] = 0;

    if (seq_count[index] >= 3) return false;
    if (c == 'L') has_l = true;
  }

  return has_l;
}

int64_t num_pleasant(std::string &s, int index) {
  if (index >= s.size()) {
    return is_valid(s);
  }

  char c{s[index]};

  int next_underscore = s.find('_', index + 1);
  int64_t count{0};

  s[index] = 'L';
  count += num_pleasant(s, next_underscore);

  s[index] = 'A';
  count += 5 * num_pleasant(s, next_underscore);

  s[index] = 'B';
  count += 20 * num_pleasant(s, next_underscore);

  s[index] = '_';

  return count;
}

int main() {
  std::string s;
  std::cin >> s;

  std::cout << num_pleasant(s, s.find('_')) << '\n';

  return 0;
}
