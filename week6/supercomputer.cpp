#include <cstddef>
#include <iostream>
#include <vector>

struct Node {
  std::size_t left, right, acc;
};

class SegmentTree {
 public:
  SegmentTree(std::size_t n) : mem(n + 1, false), tree(4 * n) {
    tree[1] = {.left = 1, .right = n, .acc = 0};
    build_tree(1);
  }
  void flip(std::size_t pos, std::size_t cur = 1);
  std::size_t query(std::size_t s, std::size_t e, std::size_t cur = 1);

  void log() {
    for (int i{1}; i < tree.size(); i++) {
      std::cerr << "tree[" << i << "]:\n";
      std::cerr << "(left, right, acc) = (" << tree[i].left << ", "
                << tree[i].right << ", " << tree[i].acc << ")\n";
    }
  }

 private:
  void build_tree(std::size_t cur);

  std::vector<bool> mem;
  std::vector<Node> tree;
};

void SegmentTree::build_tree(std::size_t cur) {
  auto &cur_node = tree[cur];

  if (cur_node.left == cur_node.right) return;

  std::size_t mid = (cur_node.left + cur_node.right) / 2;

  tree[2 * cur] = {
      .left = cur_node.left,
      .right = mid,
      .acc = 0,
  };
  build_tree(2 * cur);

  tree[2 * cur + 1] = {
      .left = mid + 1,
      .right = cur_node.right,
      .acc = 0,
  };
  build_tree(2 * cur + 1);
}

void SegmentTree::flip(std::size_t pos, std::size_t cur) {
  auto &cur_node = tree[cur];
  if (cur_node.left == cur_node.right) {
    mem[pos] = !mem[pos];
    cur_node.acc = mem[pos];
    return;
  }

  std::size_t mid = (cur_node.left + cur_node.right) / 2;

  if (pos <= mid)
    flip(pos, 2 * cur);
  else
    flip(pos, 2 * cur + 1);

  cur_node.acc = tree[2 * cur].acc + tree[2 * cur + 1].acc;
}

std::size_t SegmentTree::query(std::size_t s, std::size_t e, std::size_t cur) {
  auto &cur_node = tree[cur];

  if (s == cur_node.left and e == cur_node.right) {
    return cur_node.acc;
  }

  std::size_t mid{(cur_node.left + cur_node.right) / 2};

  if (e <= mid) {
    return query(s, e, 2 * cur);
  }

  if (s > mid) {
    return query(s, e, 2 * cur + 1);
  }

  return query(s, mid, 2 * cur) + query(mid + 1, e, 2 * cur + 1);
}

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  std::size_t n, k;
  std::cin >> n >> k;
  SegmentTree st{n};

  for (int i = 0; i < k; i++) {
    char op;
    std::cin >> op;

    if (op == 'F') {
      std::size_t pos;
      std::cin >> pos;

      st.flip(pos);
    } else {
      std::size_t s, e;
      std::cin >> s >> e;

      std::cout << st.query(s, e) << '\n';
    }
  }

  return 0;
}
