#include <bits/stdc++.h>
using namespace std;

vector<vector<long>> cache(31, vector<long>(31, -1));

long dp(long N, long M) {
  long& ans = cache[N][M];
  if (ans != -1) {
    return ans;
  }
  if (N == 1) {
    ans = M;
    return ans;
  }
  ans = 0;
  for (long i = 0; i < M - N + 1; ++i) {
    ans += dp(N - 1, M - 1 - i);
  }
  return ans;
}

void solve() {
  long N, M;
  cin >> N >> M;
  cout << dp(N, M) << "\n";
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    solve();
  }

  return 0;
}
