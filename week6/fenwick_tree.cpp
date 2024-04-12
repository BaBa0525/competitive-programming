#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>

class FenwickTree {
 public:
  FenwickTree(std::size_t size) : tree(size + 1, 0) {}
  void update(std::size_t pos, int64_t val);
  int64_t query(std::size_t pos);

 private:
  std::vector<int64_t> tree;

  std::size_t left_ancestor(std::size_t idx);
  std::size_t right_ancestor(std::size_t idx);

  std::size_t lnzb(std::size_t n);
};

void FenwickTree::update(std::size_t pos, int64_t val) {
  /* 1 indexed */
  pos += 1;

  while (pos < tree.size()) {
    tree[pos] += val;
    pos = right_ancestor(pos);
  }
}

int64_t FenwickTree::query(std::size_t pos) {
  int64_t sum{0};

  while (pos != 0) {
    sum += tree[pos];

    pos = left_ancestor(pos);
  }

  return sum;
}

std::size_t FenwickTree::left_ancestor(std::size_t idx) {
  return idx - lnzb(idx);
}

std::size_t FenwickTree::right_ancestor(std::size_t idx) {
  return idx + lnzb(idx);
}

std::size_t FenwickTree::lnzb(std::size_t idx) { return idx & (~idx + 1); }

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  std::size_t n_elements, n_ops;
  std::cin >> n_elements >> n_ops;

  FenwickTree tree{n_elements};

  for (std::size_t i{0}; i < n_ops; i++) {
    char op;
    std::cin >> op;

    switch (op) {
      case '+': {
        std::size_t idx;
        int val;

        std::cin >> idx >> val;
        tree.update(idx, val);
        break;
      }
      case '?': {
        std::size_t idx;
        std::cin >> idx;

        std::cout << tree.query(idx) << '\n';
        break;
      }
    }
  }

  return 0;
}
