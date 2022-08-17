#include <bits/stdc++.h>
using namespace std;

class Gear {
  unsigned char teeth_ = 0;

 public:

  void rotate(int direction) {
    if (direction == 1) {
      teeth_ = (teeth_ >> 1) | (teeth_ << 7);
    }
    else if (direction == -1) {
      teeth_ = (teeth_ << 1) | (teeth_ >> 7);
    }
  }

  bool top() const { return (teeth_ >> 7) & 1; }
  bool right() const { return (teeth_ >> 5) & 1; }
  bool left() const { return (teeth_ >> 1) & 1; }
  
  friend istream& operator>>(istream& istr, Gear& rhs) {
    for (int i = 7; i >= 0; --i) {
      char c;
      istr >> c;
      rhs.teeth_ |= (unsigned char)(c == '1') << i;
    }
    return istr;
  }
};

void solve() {
  Gear gears[4];
  cin >> gears[0] >> gears[1] >> gears[2] >> gears[3];

  int K;
  cin >> K;
  while (K--) {
    int i, dirs[4] = {0};
    cin >> i;
    cin >> dirs[--i];
    for (int j = i; j + 1 < 4; ++j) {
      int k = j + 1;
      if (gears[j].right() ^ gears[k].left()) {
        dirs[k] = -dirs[j];
      }
      else {
        //break;
      }
    }
    for (int j = i; j - 1 >= 0; --j) {
      int k = j - 1;
      if (gears[j].left() ^ gears[k].right()) {
        dirs[k] = -dirs[j];
      }
      else {
        //break;
      }
    }
    
    for (int j = 0; j < 4; ++j) {
      gears[j].rotate(dirs[j]);
    }
  }
  int ans = 0;
  for (int i = 0; i < 4; ++i) {
    ans += int(gears[i].top()) << i;
  }
  printf("%d\n", ans);
  
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
