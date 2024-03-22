#include <cmath>
#include <iostream>
#include <map>
#include <string>

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  int x;
  while (std::cin >> x && x != 0) {
    std::string s, p, c, m;
    std::cin >> s >> p >> c;
    m.resize(c.size());

    int n = c.size();
    int d = (int)(pow(n, 1.5) + x) % n;

    std::map<char, int> smap;
    for (int i = 0; i < s.size(); i++) {
      smap[s[i]] = i;
    }

    std::size_t id = smap[c[d]];
    m[d] = p[id];

    for (int i = (d - 1 + n) % n; i != d; i = (i - 1 + n) % n) {
      std::size_t mid = smap[m[(i + 1) % n]], cid = smap[c[i]];
      cid ^= mid;
      m[i] = p[cid];
    }
    std::cout << m << "\n";
  }

  return 0;
}
