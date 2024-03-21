// FIXME: debug
#include <algorithm>
#include <array>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using u64 = std::uint64_t;
constexpr std::size_t MAX_DIGIT = 18;
constexpr u64 CARRY_BOUND = 1e18;

class BigInt {
public:
  BigInt() : digits(1, 0){};
  BigInt(int a) { this->digits.push_back(a); }
  BigInt(const std::string &a) {
    int num_digits = a.size() - 1;

    while (num_digits >= 0) {
      std::size_t index = 1;
      this->digits.push_back(0);

      for (int i = 0; i < MAX_DIGIT && num_digits >= 0; i++) {
        this->digits.back() += index * (a[num_digits] - '0');
        index *= 10;
        num_digits -= 1;
      }
    }
  }

  BigInt &operator+=(const int other) {
    this->digits.front() += other;
    if (this->digits.front() >= CARRY_BOUND) {
      this->digits.front() %= CARRY_BOUND;
      if (this->digits.size() == 1) {
        this->digits.push_back(0);
      }
      this->digits[1] += 1;
    }

    return *this;
  }

  BigInt &operator+=(const BigInt &other) {
    if (this->digits.size() > other.digits.size()) {
      for (std::size_t i = 0; i < other.digits.size(); i++) {
        this->digits[i] += other.digits[i];

        if (this->digits[i] >= CARRY_BOUND) {
          this->digits[i] %= CARRY_BOUND;
          this->digits[i + 1] += 1;
        }
      }

      return *this;
    }

    auto new_size = std::max(this->digits.size(), other.digits.size()) + 1;
    this->digits.resize(new_size);

    for (std::size_t i = 0; i < new_size - 1; i++) {
      this->digits[i] += other.digits[i];

      if (this->digits[i] >= CARRY_BOUND) {
        this->digits[i] %= CARRY_BOUND;
        this->digits[i + 1] += 1;
      }
    }

    while (this->digits.back() == 0) {
      this->digits.pop_back();
    }
    return *this;
  }

  BigInt operator=(const BigInt &other) {
    this->digits = other.digits;
    return *this;
  }

  BigInt operator+(const BigInt &other) {
    BigInt tmp;

    tmp = *this;
    tmp += other;
    return std::move(tmp);
  }

  bool operator!=(const BigInt &other) { return this->digits != other.digits; }

  friend std::ostream &operator<<(std::ostream &stream, const BigInt &num);

private:
  std::vector<u64> digits;
};

std::ostream &operator<<(std::ostream &stream, const BigInt &num) {
  for (auto it = num.digits.rbegin(); it != num.digits.rend(); it++) {
    if (it != num.digits.rbegin()) {
      stream << std::setfill('0') << std::setw(MAX_DIGIT) << *it;
    } else {
      stream << std::setw(0) << *it;
    }
  }

  return stream;
}

std::array<std::array<BigInt, 100>, 100> results;

BigInt f(int x, int y, std::vector<std::pair<int, int>> &params) {
  auto [c, d] = params.back();

  if (x <= 0 || y <= 0) {
    return BigInt(d);
  }

  if (results[x][y] != BigInt(0)) {
    return results[x][y];
  }

  for (int i = 0; i < params.size() - 1; i++) {
    auto [a, b] = params[i];
    results[x][y] += f(x - a, y - b, params);
  }
  results[x][y] += c;

  return results[x][y];
}

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  int n;
  std::cin >> n;
  std::cin.get();

  while (n--) {
    std::string line;
    std::getline(std::cin, line);

    std::vector<std::pair<int, int>> params;
    std::stringstream ss(line);
    int a, b;
    while (ss >> a && ss >> b) {
      params.emplace_back(a, b);
    }

    std::getline(std::cin, line);

    ss.clear();
    ss.str(line);

    int x, y;
    while (ss >> x >> y) {
      std::cout << f(x, y, params) << "\n";
    }
    std::cout << "\n";
  }

  return 0;
}
