#include <cstddef>
#include <iostream>
#include <queue>
#include <vector>

#define dbg(x)                                                                \
  std::cout << "[" << __FILE__ << ":" << __LINE__ << " (" << __func__ << ")]" \
            << #x << " = " << x << std::endl;

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

struct Dist {
  size_t from, to;
  size_t dist;
};

bool operator>(const Dist &a, const Dist &b) { return a.dist > b.dist; }

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  size_t n;
  std::cin >> n;

  std::priority_queue<Dist, std::vector<Dist>, std::greater<Dist>> pq;

  for (size_t i{0}; i < n; i++) {
    for (size_t j{0}; j < n; j++) {
      size_t d;
      std::cin >> d;
      if (j < i + 1) continue;
      pq.push({i + 1, j + 1, d});
    }
  }

  DisjointSet ds{n + 1};
  while (!pq.empty()) {
    auto [from, to, dist] = pq.top();
    pq.pop();

    if (ds.find(from) == ds.find(to)) continue;
    ds.merge(from, to);
    std::cout << from << ' ' << to << '\n';
  }

  return 0;
}
