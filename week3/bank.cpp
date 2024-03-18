#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

class Customer {
public:
  Customer(int money, int time) : money(money), time(time) {}
  int money;
  int time;

  // for std::greater
  bool operator>(const Customer &other) const {
    if (this->money != other.money) {
      return this->money > other.money;
    }

    return this->time > other.time;
  }
};

int main() {

  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  int n_guest, m_close;
  std::cin >> n_guest >> m_close;

  std::vector<Customer> customers;
  customers.reserve(n_guest);

  for (int i = 0; i < n_guest; i++) {
    int m, t;
    std::cin >> m >> t;
    customers.emplace_back(m, t);
  }

  std::sort(customers.begin(), customers.end(), std::greater<Customer>());

  std::set<int> available;
  for (int i = 0; i <= m_close; i++) {
    available.insert(i);
  }

  unsigned int total_money = 0;
  for (auto &c : customers) {
    if (available.empty()) {
      break;
    }

    auto it = available.upper_bound(c.time);
    if (it == available.begin()) {
      continue;
    }

    available.erase(--it);
    total_money += c.money;
  }

  std::cout << total_money << "\n";

  return 0;
}
