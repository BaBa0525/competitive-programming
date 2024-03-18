#include <iostream>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int year{}, month{}, date{};
  char split_ch;
  std::cin >> year >> split_ch >> month >> split_ch >> date;

  if (year > 2023) {
    std::cout << "GOOD\n";
    return 0;
  }

  if (year < 2023) {
    std::cout << "TOO LATE\n";
    return 0;
  }

  int gap = (10 - month) * 30 + 21 - date;
  if (gap < 35) {
    std::cout << "TOO LATE\n";
    return 0;
  }

  std::cout << "GOOD\n";

  return 0;
}
