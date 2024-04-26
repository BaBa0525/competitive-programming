#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

struct DisjointSet {
  std::vector<int> head;
  DisjointSet (int n): head(n, -1) {}

  int find(int x) {
    return head[x] < 0 ? x : head[x] = find(head[x]);
  }

  void merge(int x, int y) {
    int px {find(x)}, py {find(y)};
    if (px == py) return;

    if (head[px] > head[py]) std::swap(px, py);

    head[px] += head[py];
    head[py] = px;
  }
};


struct Edge {
  int u, v, w;
  Edge(int u, int v, int w): u(u), v(v), w(w) {}
};

bool edge_cmp(const Edge &e1, const Edge &e2) {
  return e1.w < e2.w;
}


int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  int n, m;
  while (std::cin >> n >> m and !(n == 0 and m == 0)) {
    std::vector<Edge> edges;
    edges.reserve(m);

    for (int i {0}; i < m; i++) {
      int u, v, w;
      std::cin >> u >> v >> w;
      edges.emplace_back(u, v, w);
    }

    if (m < n-1) {
      std::cout << "Impossible\n";
      continue;
    }

    std::sort(edges.begin(), edges.end(), edge_cmp);
    DisjointSet ds {n};

    std::vector<std::pair<int, int>> selected_edges;
    int total {0};
    for (int i {0}; i < m; i++) {
      auto [u, v, w] = edges[i]; 

      if (ds.find(u) == ds.find(v)) continue;
      ds.merge(u, v);

      total += w;

      if (u > v) std::swap(u, v);
      selected_edges.emplace_back(u, v);

      if (selected_edges.size() == n - 1) break;
    }

    if (selected_edges.size() != n - 1) {
      std::cout << "Impossible\n";
      continue;
    }

    std::sort(selected_edges.begin(), selected_edges.end());

    std::cout << total << '\n';
    for (auto [u, v] : selected_edges) {
      std::cout << u << ' ' << v << '\n';
    }
  }

  
  return 0;
}
