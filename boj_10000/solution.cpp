#include <bits/stdc++.h>
using namespace std;

struct Circle {
  int l;
  int r;


  bool contains(const Circle& other) const {
    return l <= other.l && other.r <= r;
  }

  friend istream& operator>>(istream& istr, Circle& c) {
    int x, r;
    istr >> x >> r;
    c.l = x - r;
    c.r = x + r;
    return istr;
  }
};

void solve() {
  int N;
  cin >> N;

  vector<Circle> circles(N);
  for (int i = 0; i < N; ++i) {
    cin >> circles[i];
  }

  int ans = 0;
  sort(circles.begin(), circles.end(),
       [](const auto& lhs, const auto& rhs) -> bool {
         if (lhs.r == rhs.r) {
           return lhs.l > rhs.l;
         }
         return lhs.r < rhs.r;
       });

  //for (const auto& c : circles) {
    //cout << c.l << ", " << c.r << "\n";
  //}
  stack<int> s;
  for (int i = 0; i < N; ++i) {
    const auto& c = circles[i];
    if (s.empty() || circles[s.top()].r <= c.l) {
      s.push(i);
      continue;
    }
    bool closed = true;
    int x = c.r;
    Circle* inner = nullptr;
    while (!s.empty() && c.contains(circles[s.top()])) {
      inner = &circles[s.top()];
      s.pop();
      closed &= inner->r == x;
      x = inner->l;
      ans += 1;
    }
    closed &= (inner != nullptr && inner->l == c.l);
    ans += closed;
    s.push(i);
  }
  ans += s.size() + 1;
  cout << ans << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
