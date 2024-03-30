#include <cstddef>
#include <iostream>
#include <vector>

#define dbg(x)                                                                 \
  std::cout << "[" << __FILE__ << ":" << __LINE__ << " (" << __func__ << ")] " \
            << #x << " = " << x << std::endl;

using std::size_t;

class Terrace {
 public:
  Terrace(size_t n) : head(n, -1), valid(n, true) {}
  size_t find(size_t a);
  void merge(size_t a, size_t b);

  std::vector<int> head;
  std::vector<bool> valid;
};

size_t Terrace::find(size_t a) {
  return head[a] < 0 ? a : head[a] = find(head[a]);
}

void Terrace::merge(size_t a, size_t b) {
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

bool within(int x, int a, int b) { return x >= a && x <= b; }

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  size_t n, m;
  std::cin >> n >> m;

  Terrace t(n * m);
  std::vector<std::vector<size_t>> height(m, std::vector<size_t>(n));

  for (auto &r : height) {
    for (auto &h : r) std::cin >> h;
  }

  int x_move[] = {0, 1, 0, -1};
  int y_move[] = {1, 0, -1, 0};

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < 4; k++) {
        int x = j + x_move[k];
        int y = i + y_move[k];
        if (!within(x, 0, n - 1)) continue;
        if (!within(y, 0, m - 1)) continue;
        if (height[y][x] != height[i][j]) continue;
        t.merge(y * n + x, i * n + j);
      }
    }
  }

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < 4; k++) {
        int x = j + x_move[k];
        int y = i + y_move[k];
        if (!within(x, 0, n - 1)) continue;
        if (!within(y, 0, m - 1)) continue;
        if (height[i][j] <= height[y][x]) continue;
        t.valid[t.find(i * n + j)] = false;
      }
    }
  }

  size_t sum = 0;
  for (int i = 0; i < m * n; i++) {
    if (t.valid[i] == false || t.head[i] > 0) continue;
    sum += -t.head[i];
  }

  std::cout << sum << "\n";

  return 0;
}
