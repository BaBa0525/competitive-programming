#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

struct DisjointSet {
  std::vector<int> head;
  DisjointSet(int n) : head(n, -1) {}

  int find(int x) { return head[x] < 0 ? x : head[x] = find(head[x]); }

  void merge(int x, int y) {
    int px{find(x)}, py{find(y)};
    if (px == py) return;

    if (head[px] < head[py]) std::swap(px, py);
    head[py] += head[px];
    head[px] = py;
  }
};

struct Node {
  Node(int dep, int r, int c) : dep(dep), r(r), c(c) {}
  int dep;
  int r, c;
};

bool operator>(const Node& n1, const Node& n2) { return n1.dep > n2.dep; }

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  int r, c;
  std::cin >> r >> c;

  std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;

  for (int i{0}; i < r; i++) {
    for (int j{0}; j < c; j++) {
      int dep;
      std::cin >> dep;
      pq.emplace(dep, i, j);
    }
  }

  auto get_1d_idx = [&](int i, int j) { return i * c + j + 1; };

  DisjointSet ds{r * c + 2};
  std::vector<bool> visited(r * c + 2, false);
  visited.front() = true;
  visited.back() = true;

  while (!pq.empty()) {
    auto [dep, i, j] = pq.top();
    pq.pop();

    // std::cout << "dep = " << dep << ", ";
    // std::cout << "i = " << i << ", ";
    // std::cout << "j = " << j << ", ";

    auto idx = get_1d_idx(i, j);
    visited[idx] = true;
    // std::cout << "idx = " << idx << '\n';

    if (j == 0) {
      // std::cout << "merge: 0 0, " << i << ' ' << j << '\n';
      ds.merge(0, idx);
    }
    if (j == c - 1) {
      // std::cout << "merge: end, " << i << ' ' << j << '\n';
      ds.merge(idx, r * c + 1);
    }

    if (i - 1 >= 0) {
      int other = get_1d_idx(i - 1, j);
      if (visited[other]) {
        // std::cout << "merge: " << i-1 << ' ' <<  j << ", " << i << ' ' << j
        // << '\n';
        ds.merge(other, idx);
      }
    }

    if (j + 1 < c) {
      int other = get_1d_idx(i, j + 1);
      if (visited[other]) {
        // std::cout << "merge: " << i << ' ' <<  j+1 << ", " << i << ' ' << j
        // << '\n';
        ds.merge(other, idx);
      }
    }

    if (i + 1 < r) {
      int other = get_1d_idx(i + 1, j);
      if (visited[other]) {
        // std::cout << "merge: " << i+1 << ' ' <<  j << ", " << i << ' ' << j
        // << '\n';
        ds.merge(other, idx);
      }
    }

    if (j - 1 >= 0) {
      int other = get_1d_idx(i, j - 1);
      if (visited[other]) {
        // std::cout << "merge: " << i << ' ' <<  j-1 << ", " << i << ' ' << j
        // << '\n';
        ds.merge(other, idx);
      }
    }

    if (ds.find(0) == ds.find(r * c + 1)) {
      std::cout << dep << '\n';
      break;
    }
  }

  return 0;
}
