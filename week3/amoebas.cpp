#include <array>
#include <cstddef>
#include <iostream>
#include <queue>
#include <vector>

struct Pos {
  int x, y;

  Pos &operator+=(const Pos &other) {
    this->x += other.x;
    this->y += other.y;
    return *this;
  }

  Pos operator+(const Pos &other) const {
    auto tmp = *this;
    tmp += other;
    return tmp;
  }

  bool x_within(int a, int b) const { return this->x >= a && this->x < b; }
  bool y_within(int a, int b) const { return this->y >= a && this->y < b; }
};

template <typename T> using Matrix = std::vector<std::vector<T>>;

constexpr std::array<Pos, 8> moves = {
    {{1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}} //
};

void remove_adj(Matrix<char> &graph, const Pos &start) {
  int n = graph.size(), m = graph.begin()->size();

  std::queue<Pos> q;
  q.push(start);

  while (!q.empty()) {
    auto p = q.front();
    graph[p.x][p.y] = '.';
    q.pop();

    for (const auto &move : moves) {
      auto tmp = p + move;

      if (!tmp.x_within(0, n) || !tmp.y_within(0, m)) {
        continue;
      }
      if (graph[tmp.x][tmp.y] == '.') {
        continue;
      }

      q.push(tmp);
    }
  }
}

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  int n, m;
  std::cin >> n >> m;

  Matrix<char> graph(n, std::vector<char>(m));

  for (auto &i : graph) {
    for (auto &j : i) {
      std::cin >> j;
    }
  }

  std::size_t loop_count{};
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (graph[i][j] == '.') {
        continue;
      }

      loop_count++;
      remove_adj(graph, Pos{i, j});
    }
  }

  std::cout << loop_count << '\n';

  return 0;
}
