#include <cstddef>
#include <deque>
#include <iostream>
#include <vector>

using std::size_t;

/* In this solution, we can imagine that we construct 2 graphs for forced edges
 * which are [1, n] and [n+1, 2n]. Normal edges are connected between two
 * graphs.
 */
int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  size_t n, m;
  std::cin >> n >> m;

  /* [1, n] for forced edges, [n+1, 2n] for normal edges */
  std::vector<std::vector<int>> adj(2 * n + 1);

  /* for those stop without bug */
  for (size_t i{1}; i <= n; i++) {
    adj[i + n].push_back(i);
  }

  for (size_t i{0}; i < m; i++) {
    int a, b;
    std::cin >> a >> b;
    if (a > 0) {
      adj[a + n].push_back(b);
      continue;
    }

    adj[-a].push_back(b);
    adj[-a + n].push_back(b + n);
  }
  std::deque<size_t> q{n + 1};
  std::vector<bool> visited(2 * n + 1, false);
  visited[n + 1] = true;

  size_t ans{0};
  while (!q.empty()) {
    auto node{q.front()};
    q.pop_front();

    if (adj[node].empty()) {
      ans++;
      continue;
    }

    for (auto to : adj[node]) {
      if (visited[to]) continue;
      q.push_back(to);
      visited[to] = true;
    }
  }

  std::cout << ans << "\n";

  return 0;
}
