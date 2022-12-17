#include <bits/stdc++.h>
using namespace std;

template <typename array_t>
vector<int> zAlgorithm(const array_t& s) {
  int n = s.size();
  vector<int> z(s.size(), 0);
  if (s.empty())
    return z;
  z[0] = n;

  int l = 0, r = 0;
  for (int i = 1; i < s.size(); ++i) {
    if (i > r) {
      l = r = i;
      while (r < n && s[r - l] == s[r])
        r++;
      z[i] = r - l;
      r--;
    } else {
      int k = i - l;
      if (z[k] < r - i + 1)
        z[i] = z[k];
      else {
        l = i;
        while (r < n && s[r - l] == s[r])
          r++;
        z[i] = r - l;
        r--;
      }
    }
  }
  return z;
}

void solve() {
  string s;
  cin >> s;
  reverse(s.begin(), s.end());
  auto z = zAlgorithm(s);
  reverse(z.begin(), z.end());

  int Q;
  cin >> Q;
  while (Q--) {
    int i;
    cin >> i;
    cout << z[--i] << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);

  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
