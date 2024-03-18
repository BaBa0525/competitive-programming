#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using ull = unsigned long long;

class BigInt {
public:
  std::vector<int> digits;

  ull get_last_n_digits(int n) {
    ull val = 0;
    for (int i = 0; i < n; i++) {
      if (i == digits.size()) {
        return val;
      }

      val += digits[digits.size() - 1 - i] * pow(10, i);
    }

    return val;
  }

  void remove_last_n_digits(int n) {
    while (n--) {
      digits.pop_back();
    }
  }
};

std::istream &operator>>(std::istream &stream, BigInt &num) {
  std::string digits;
  stream >> digits;
  for (auto &d : digits) {
    num.digits.push_back(d - '0');
  }

  return stream;
}

int main() {
  BigInt big_num;
  ull b;
  std::cin >> big_num >> b;

  int comma_num = 0;

  while (big_num.digits.size() > 0) {
    std::cerr << big_num.digits.size() << std::endl;
    int num_digits = 0;
    while (b >= big_num.get_last_n_digits(num_digits + 1)) {
      num_digits++;

      if (num_digits == big_num.digits.size()) {
        break;
      }
    }

    if (num_digits == 0) {
      std::cout << "NO WAY\n";
      return 0;
    }

    if (big_num.digits.size() == num_digits) {
      break;
    }

    while (big_num.digits[big_num.digits.size() - num_digits] == 0) {
      num_digits--;

      if (num_digits == 0) {
        std::cout << "NO WAY\n";
        return 0;
      }
    }

    b = big_num.get_last_n_digits(num_digits);
    big_num.remove_last_n_digits(num_digits);
    comma_num++;
  }

  std::cout << comma_num << '\n';

  return 0;
}
