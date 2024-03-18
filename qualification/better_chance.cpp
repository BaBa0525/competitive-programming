#include <iostream>
#include <cmath>
 
int main() {
  int rt, rj;
  std::cin >> rt >> rj;
 
  double st_db, sj_db;
  std::cin >> st_db >> sj_db;
 
  int st = round(st_db * 100);
  int sj = round(sj_db * 100);
 
  int taoyuan = (rt - 1) * sj;
  int jakarta = (rj - 1) * st;
 
  if (taoyuan < jakarta) {
    std::cout << "TAOYUAN\n";
    return 0;
  }
 
  if (taoyuan > jakarta) {
    std::cout << "JAKARTA\n";
    return 0;
  }
 
  std::cout << "SAME\n";
  return 0;
}
