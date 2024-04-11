#include <iostream>
#include <vector>

#define log_val(x)                                                     \
  do {                                                                 \
    std::cout << "[" << __FILE__ << ":" << __LINE__ << "(" << __func__ \
              << ")] " << #x << " = " << x << std::endl;               \
  } while (0)

/* also called binary indexed tree (BIT) */
class FenwickTree {
 public:
  FenwickTree(const std::vector<int> &s) : tree(s.size() + 1, 0) {
    /* we can use this->update to init frenwick tree, but this takes
       O(n * logn). So we use this method instead. */
    for (int i = 0; i < s.size(); i++) {
      tree[i + 1] += s[i];

      /* go to the closest right ancestor */
      int j = (i + 1) + lnzb(i + 1);

      if (j >= tree.size()) continue;
      tree[j] += tree[i + 1];
    }
  }

  /* lowest not zero-bit */
  int lnzb(int n);
  int prefix_sum(int n);

  /* range sum of [s, e] */
  int range_sum(int s, int e);
  void update(int n, int val);

  void log();

 private:
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

void FenwickTree::log() {
  for (int i = 1; i < tree.size(); i++) {
    log_val(tree[i]);
  }
}

int main() {
  std::vector<int> s{10, 6, 3, 4, 2, 9, 7, 5, 11, 1, 8};
  FenwickTree fw_tree(s);
  fw_tree.log();

  while (true) {
    int s, e;
    std::cin >> s >> e;
    log_val(fw_tree.range_sum(s, e));
  }

  return 0;
}
