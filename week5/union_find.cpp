#include <cstddef>
#include <iostream>
#include <vector>

using std::size_t;

class DisjointSet {
 public:
  DisjointSet(size_t n) : head(n, -1) {}
  int find(int a);
  void merge(int a, int b);

 private:
  std::vector<int> head;
};

int DisjointSet::find(int a) {
  return head[a] < 0 ? a : head[a] = find(head[a]);
}

void DisjointSet::merge(int a, int b) {
  a = find(a);
  b = find(b);

  if (a == b) return;

  if (head[a] < head[b]) {
    head[a] += head[b];
    head[b] = a;
    return;
  }

  head[b] += head[a];
  head[a] = b;
}

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  size_t n, q;
  std::cin >> n >> q;
  DisjointSet ds{n};

  for (size_t i{0}; i < q; i++) {
    char cmd;
    int a, b;
    std::cin >> cmd >> a >> b;

    switch (cmd) {
      case '=':
        ds.merge(a, b);
        break;
      case '?':
        std::cout << ((ds.find(a) == ds.find(b)) ? "yes\n" : "no\n");
        break;
      default:
        break;
    }
  }

  return 0;
}
