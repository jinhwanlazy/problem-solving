#include <bits/stdc++.h>
using namespace std;

struct Cartridges {
  int inks[4] = {0};
  int& c = inks[0];
  int& m = inks[1];
  int& y = inks[2];
  int& k = inks[3];

  int sum() { return c + m + y + k; }
};

ostream& operator<<(ostream& os, const Cartridges& c) {
  os << c.c << " " << c.m << " " << c.y << " " << c.k;
  return os;
}

istream& operator>>(istream& is, Cartridges& c) {
  is >> c.c >> c.m >> c.y >> c.k;
  return is;
}

int min(int a, int b, int c) {
  a = min(a, b);
  a = min(a, c);
  return a;
}

Cartridges solution() {
  Cartridges a, b, c;
  cin >> a >> b >> c;

  Cartridges res;
  for (int i = 0; i < 4; ++i) {
    res.inks[i] = min(a.inks[i], b.inks[i], c.inks[i]);
  }
  if (res.sum() <= 1e6) {
    return res;
  }
  for (int i = 0; i < 4; ++i) {
    if (res.sum() - res.inks[i] >= 1e6)
      res.inks[i] = 0;
  }
  if (res.sum() <= 1e6) {
    return res;
  }
  for (int i = 0; i < 4; ++i) {
    int sum = res.sum();
    if (sum == 1e6) {
      break;
    }
    if (sum - res.inks[i] <= 1e6)
      res.inks[i] -= sum - 1e6;
  }
  return res;
}

int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    cout << "Case #" << t << ": ";
    auto res = solution();
    if (res.sum() == 1e6) {
      cout << res << "\n";
    } else {
      cout << "IMPOSSIBLE"
           << "\n";
    }
  }
  return 0;
}
