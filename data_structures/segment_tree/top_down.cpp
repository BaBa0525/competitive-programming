#include <algorithm>
#include <iostream>
#include <vector>

#define log_val(x) std::cerr << #x << " = " << x << std::endl;

struct Node {
  int left, right, val;
};

using Strategy = int (*)(int a, int b);

class SegmentTree {
 public:
  /* four times to ensure enough nodes */
  SegmentTree(const std::vector<int> &vec, Strategy s)
      : tree(4 * vec.size()), val_arr(vec), strategy(s) {
    tree[1].left = 0, tree[1].right = vec.size() - 1;
    build_tree(1);
  }

  void update(int pos, int val) { _update(pos, val, 1); }
  int query(int left, int right) { return _query(left, right, 1); }
  void log_all();

 private:
  void _update(int pos, int val, int cur);
  int _query(int left, int right, int cur);
  void build_tree(int cur);

  Strategy strategy;
  std::vector<int> val_arr;
  std::vector<Node> tree;
};

/* O(n) */
void SegmentTree::build_tree(int cur) {
  auto [left, right, _] = tree[cur];
  if (left == right) {
    tree[cur].val = val_arr[left];
    return;
  }

  int m = (left + right) / 2;

  tree[cur * 2].left = left;
  tree[cur * 2].right = m;

  tree[cur * 2 + 1].left = m + 1;
  tree[cur * 2 + 1].right = right;

  build_tree(cur * 2);
  build_tree(cur * 2 + 1);

  tree[cur].val = strategy(tree[cur * 2].val, tree[cur * 2 + 1].val);
}

/* O(logn) */
void SegmentTree::_update(int pos, int val, int cur) {
  auto &cur_node = tree[cur];
  if (cur_node.left == tree[cur].right) {
    cur_node.val = val;
    return;
  }

  int m = (cur_node.left + cur_node.right) / 2;
  if (pos <= m) {
    _update(pos, val, 2 * cur);
  } else {
    _update(pos, val, 2 * cur + 1);
  }
  cur_node.val = strategy(tree[cur * 2].val, tree[cur * 2 + 1].val);
}

/* O(logn) */
int SegmentTree::_query(int left, int right, int cur) {
  auto &cur_node = tree[cur];
  if (left == cur_node.left and right == cur_node.right) {
    return cur_node.val;
  }

  int m = (cur_node.left + cur_node.right) / 2;
  if (right <= m) {
    return _query(left, right, 2 * cur);
  }

  if (m < left) {
    return _query(left, right, 2 * cur + 1);
  }

  return strategy(_query(left, m, 2 * cur), _query(m + 1, right, 2 * cur + 1));
}

int main() {
  std::vector<int> arr{10, 3, 11, 4, 2, 9, 7, 5};
  Strategy max_s = [](int a, int b) { return std::max(a, b); };
  Strategy min_s = [](int a, int b) { return std::min(a, b); };
  Strategy acc_s = [](int a, int b) { return a + b; };
  SegmentTree seg_tree{arr, acc_s};

  log_val(seg_tree.query(3, 5));

  return 0;
}

void SegmentTree::log_all() {
  std::cerr << "---Segment Tree---" << std::endl;
  for (int i = 0; i < tree.size(); i++) {
    std::cerr << i << ": ";
    log_val(tree[i].val);
  }
}
