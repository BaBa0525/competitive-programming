#include <array>
#include <cstddef>
#include <iostream>
#include <vector>

using u64 = unsigned long long;

struct Node {
  std::array<int, 7> gem_type_count;
  int type;

  Node &operator+=(const Node &other) {
    for (int i{1}; i < 7; i++) gem_type_count[i] += other.gem_type_count[i];
    return *this;
  }
};

class FenwickTree {
 public:
  FenwickTree(const std::vector<int> &gems) : tree(gems.size() + 1) {
    for (int i = 1; i < gems.size(); i++) {
      tree[i].type = gems[i];
      tree[i].gem_type_count[gems[i]] += 1;

      int right_anc = i + ((i) & -(i));
      if (right_anc < tree.size()) {
        tree[right_anc] += tree[i];
      }
    }
  }

  void update(int pos, int new_type) {
    int old_type{tree[pos].type};
    tree[pos].type = new_type;

    while (pos < tree.size()) {
      tree[pos].gem_type_count[old_type] -= 1;
      tree[pos].gem_type_count[new_type] += 1;

      pos = pos + (pos & (-pos));
    }
  }

  std::array<int, 7> query(int pos) {
    Node sum{};

    while (pos > 0) {
      sum += tree[pos];
      pos -= (pos & -pos);
    }

    return sum.gem_type_count;
  }

 private:
  std::vector<Node> tree;
};

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  std::size_t n, q;
  std::cin >> n >> q;

  std::array<u64, 7> gem_val;

  for (int i{1}; i < gem_val.size(); i++) {
    std::cin >> gem_val[i];
  }

  std::vector<int> gems(n + 1);
  for (int i{1}; i <= n; i++) {
    char c;
    std::cin >> c;
    gems[i] = c - '0';
  }

  FenwickTree fw_tree{gems};

  for (int i{0}; i < q; i++) {
    int op;
    std::cin >> op;

    switch (op) {
      case 1: {
        int k, p;
        std::cin >> k >> p;
        fw_tree.update(k, p);
        break;
      }
      case 2: {
        int p, v;
        std::cin >> p >> v;
        gem_val[p] = v;
        break;
      }
      case 3: {
        int l, r;
        std::cin >> l >> r;

        auto a = fw_tree.query(l - 1);
        auto b = fw_tree.query(r);

        u64 total{0};
        for (int i{1}; i < 7; i++) {
          total += gem_val[i] * (b[i] - a[i]);
        }

        std::cout << total << '\n';
        break;
      }
    }
  }

  return 0;
}
