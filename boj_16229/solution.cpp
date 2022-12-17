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
  int N, K;
  scanf("%d %d", &N, &K);

  string s;
  cin >> s;

  if (K >= N) {
    printf("%d\n", min(N, (K + N) / 2));
    return;
  }

  auto z = zAlgorithm(s);
  
  int ans = (K + N) / 2;
  while (ans > 0) {
    int N_ = N;
    if (N_ % ans != 0) {
      N_ += (ans - N_ % ans);
    }
    int K_ = N_ - N;
    if (N_ > N + K) {
      ans--;
      continue;
    }
    bool good = true;
    for (int i = 0; i < N; i += ans) {
      if (z[i] + K_ < N_ - i) {
        good = false;
        break;
      }
    }
    if (good) {
      printf("%d\n", ans);
      return;
    }
    ans--;
  }
  printf("%d\n", 0);

}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
