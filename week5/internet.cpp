#include <cstddef>
#include <iostream>
#include <vector>

#define dbg(x)                                                             \
  do {                                                                     \
    std::cerr << '[' << __FILE__ << ':' << __LINE__ << "] " << #x << " = " \
              << x << std::endl;                                           \
  } while (0)

using std::size_t;

class DisjointSet {
 public:
  DisjointSet(size_t n) : head(n, -1) {}
  int merge(int a, int b);
  int find(int a);

 private:
  std::vector<int> head;
};

int DisjointSet::find(int a) {
  return head[a] < 0 ? a : head[a] = find(head[a]);
}

int DisjointSet::merge(int a, int b) {
  a = find(a);
  b = find(b);

  if (a == b) return -head[a];

  if (head[a] < head[b]) {
    head[a] += head[b];
    head[b] = a;
    return -head[a];
  }

  head[b] += head[a];
  head[a] = b;

  return -head[b];
}

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  size_t n, m;
  std::cin >> n >> m;
  DisjointSet ds(n);

  for (size_t i = 0; i < m; i++) {
    size_t a, b;
    std::cin >> a >> b;
    size_t s = ds.merge(a - 1, b - 1);
    if (s == n) {
      std::cout << "Connected\n";
      return 0;
    }
  }

  size_t p = ds.find(0);
  for (size_t i = 1; i < n; i++) {
    size_t ip = ds.find(i);
    if (ip == p) continue;
    std::cout << i + 1 << "\n";
  }

  return 0;
}
