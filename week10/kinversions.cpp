#include <complex>
#include <cstdint>
#include <iostream>
#include <valarray>

using Polynomial = std::valarray<std::complex<double>>;
const double PI = std::acos(-1);

#define print_poly(poly)            \
  do {                              \
    std::cout << #poly << ": ";     \
    for (auto p : poly) {           \
      std::cout << p.real() << " "; \
    }                               \
    std::cout << "\n";              \
  } while (0)

int64_t next_power_of_2(int64_t n) {
  /* for those n are power of two */
  n--;

  /* suppose n is 0x00100000 now */

  /* n is 0x00110000 */
  n |= n >> 1;

  /* n is 0x00111100 */
  n |= n >> 2;

  /* n is 0x00111111 */
  n |= n >> 4;

  n |= n >> 8;
  n |= n >> 16;
  n |= n >> 32;

  /* n is 0x01000000 */
  return n + 1;
}

void FFT(Polynomial& p) {
  size_t n = p.size();
  if (n <= 1) return;

  Polynomial even = p[std::slice(0, n / 2, 2)];  // even = p[::2]
  Polynomial odd = p[std::slice(1, n / 2, 2)];   // odd = p[1::2]

  FFT(even);
  FFT(odd);

  for (size_t j = 0; j < n / 2; j++) {
    /*
     * std::polar(r, theta) = r (cos(theta) + i sin(theta))
     *                      = r * std::exp(theta * 1i)
     * omega = exp(2 pi i / n) [root of unity]
     */
    std::complex<double> t = std::polar(1.0, 2.0 * PI * j / n) * odd[j];
    p[j] = even[j] + t;
    p[j + n / 2] = even[j] - t;
  }
}

void IFFT(Polynomial& p) {
  p = p.apply(std::conj);
  FFT(p);
  p = p.apply(std::conj);
  p /= p.size();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string s;
  std::cin >> s;

  int64_t size = next_power_of_2(s.size() << 1);

  Polynomial p1(size), p2(size);

  for (int64_t i = 0; i < s.size(); i++) {
    p1[i] = (s[i] == 'A') ? 1.0 : 0.0;
    p2[size - i - 1] = (s[i] == 'A') ? 0.0 : 1.0;
  }

  FFT(p1);
  FFT(p2);

  p1 *= p2;
  IFFT(p1);

  for (int i = 0; i < s.size() - 1; i++) {
    std::cout << static_cast<int>(p1[i].real() + 0.25) << '\n';
  }

  return 0;
}
