#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

std::size_t num_digits(int number, int base = 10) {
  int digits = 0;

  while (number != 0) {
    number /= 10;
    digits++;
  }

  return digits;
}

class BigInt {

public:
  BigInt() = default;
  BigInt(int a) {
    while (a != 0) {
      digits.push_back(a % 10);
      a /= 10;
    }
  };

  friend std::istream &operator>>(std::istream &stream, BigInt &a);
  friend std::ostream &operator<<(std::ostream &stream, BigInt &a);
  BigInt &operator*=(int other);
  BigInt &operator--();
  bool operator<=(const BigInt &other);

private:
  std::vector<int> digits;
};

int main() {
  BigInt n1, n2{2};

  // FIXME: k also needs to be a BigInt. Hence, we need to finish minus and
  // equal parts.
  int k;

  std::cin >> n1 >> k;
  while (k--) {
    n2 *= 2;
  }

  if (n1 <= n2) {
    std::cout << "Your wish is granted!\n";
  } else {
    std::cout << "You will become a flying monkey!\n";
  }

  return 0;
}

// -------------------- class member definition --------------------

std::istream &operator>>(std::istream &stream, BigInt &a) {
  std::string number;
  stream >> number;
  for (auto it = number.rbegin(); it != number.rend(); it++) {
    a.digits.push_back(*it - '0');
  }

  return stream;
}

std::ostream &operator<<(std::ostream &stream, BigInt &a) {
  auto &number = a.digits;
  for (auto it = number.rbegin(); it != number.rend(); it++) {
    stream << *it;
  }

  return stream;
}

BigInt &BigInt::operator*=(int other) {
  std::vector<int> buf(digits.size() + num_digits(other), 0);

  std::size_t offset = 0;
  while (other != 0) {
    int mul = other % 10;
    other /= 10;

    for (int i = 0; i < digits.size(); i++) {
      buf[i + offset] += digits[i] * mul;
    }
    offset++;
  }

  digits.resize(buf.size());

  int carry = 0;
  for (int i = 0; i < digits.size(); i++) {
    digits[i] = (buf[i] + carry) % 10;
    carry = (buf[i] + carry) / 10;
  }

  for (auto it = digits.rbegin(); *it == 0; it++) {
    digits.pop_back();
  }

  return *this;
}

bool BigInt::operator<=(const BigInt &other) {
  if (digits.size() != other.digits.size()) {
    return digits.size() < other.digits.size();
  }

  for (int i = digits.size(); i > 0; i--) {
    if (digits[i] != other.digits[i]) {
      return digits[i] < other.digits[i];
    }
  }

  return true;
}
