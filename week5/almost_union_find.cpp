#include <iostream>
#include <utility>
#include <vector>

using i64 = std::int64_t;

struct DisjointSet {
  std::vector<int> head, idx;
  std::vector<i64> sum;

  DisjointSet(int n) : head(n, -1), idx(n), sum(n) {
    for (int i{0}; i < n; i++) {
      idx[i] = sum[i] = i;
    }
  }

  // need to handle idx by caller for using both internal and external
  void merge(int a, int b) {
    int pa{find(a)}, pb{find(b)};
    if (pa == pb) return;

    if (head[pa] > head[pb]) std::swap(pa, pb);

    head[pa] += head[pb];
    sum[pa] += sum[pb];

    head[pb] = pa;
  }

  /* move a to the set containing b */
  void move(int a, int b) {
    int pa{find(idx[a])}, pb{find(idx[b])};
    if (pa == pb) return;

    head[pa] += 1;  // decrease 1
    sum[pa] -= a;

    idx[a] = head.size();

    head.push_back(-1);
    sum.push_back(a);

    merge(idx[a], pb);
  }

  i64 get_sum(int a) { return sum[find(idx[a])]; }

  int get_idx(int a) { return idx[a]; }

  int get_size(int a) { return -head[find(idx[a])]; }

  int find(int a) { return head[a] < 0 ? a : head[a] = find(head[a]); }
};

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  int n, m;
  while (std::cin >> n >> m) {
    DisjointSet ds{n + 1};

    while (m--) {
      int op;
      std::cin >> op;

      switch (op) {
        case 1: {
          int p, q;
          std::cin >> p >> q;
          ds.merge(ds.get_idx(p), ds.get_idx(q));

          // std::cout << op << ' ' << p << ' ' << q << std::endl;
          // for (int i{1}; i < ds.head.size(); i++) {
          //   std::cout << ds.head[i] << std::endl;
          // }
          // std::cout << std::endl;

          break;
        }
        case 2: {
          int p, q;
          std::cin >> p >> q;
          ds.move(p, q);

          // std::cout << op << ' ' << p << ' ' << q << std::endl;
          // for (int i{1}; i < ds.head.size(); i++) {
          //   std::cout << ds.head[i] << std::endl;
          // }
          // std::cout << std::endl;
          break;
        }
        case 3: {
          int p;
          std::cin >> p;
          std::cout << ds.get_size(p) << ' ' << ds.get_sum(p) << '\n';
          break;
        }
      }
    }
  }

  return 0;
}
