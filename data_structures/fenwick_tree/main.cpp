#include <iostream>
#include <vector>

#define log_val(x)                                                     \
  do {                                                                 \
    std::cout << "[" << __FILE__ << ":" << __LINE__ << "(" << __func__ \
              << ")] " << #x << " = " << x << std::endl;               \
  } while (0)

class FenwickTree {
 public:
  FenwickTree(const std::vector<int> &s) : tree(s.size() + 1, 0) {
    for (int i{1}; i < s.size() + 1; i++) {
      update(i, s[i - 1]);
    }

    for (int i{1}; i < tree.size(); i++) {
      log_val(tree[i]);
    }
  }

  /* lowest not zero-bit */
  int lnzb(int n);
  int prefix_sum(int n);

  /* range sum of [s, e] */
  int range_sum(int s, int e);
  void update(int n, int val);

 private:
  /* binary indexed tree */
  std::vector<int> tree;
};

int FenwickTree::lnzb(int n) { return n & (-n); }

void FenwickTree::update(int n, int val) {
  while (n < tree.size()) {
    tree[n] += val;
    n += lnzb(n);
  }
}

int FenwickTree::prefix_sum(int n) {
  int sum{0};

  while (n > 0) {
    sum += tree[n];

    /* update self to the closest left ancester */
    n = n - lnzb(n);
  }

  return sum;
}

int FenwickTree::range_sum(int s, int e) {
  return prefix_sum(e) - prefix_sum(s - 1);
}

int main() {
  std::vector<int> s{10, 6, 3, 4, 2, 9, 7, 5, 11, 1, 8};
  FenwickTree fw_tree(s);

  while (true) {
    int s, e;
    std::cin >> s >> e;
    log_val(fw_tree.range_sum(s, e));
  }

  return 0;
}
