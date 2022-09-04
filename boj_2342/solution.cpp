#include <bits/stdc++.h>
using namespace std;

constexpr static int INF = numeric_limits<int>::max() / 2;

inline int cost(int from, int to) {
  if (from == 0) return 2;
  if (from == to) return 1;
  if (from > to) swap(from, to);
  if (from == 1 && to == 3) return 4;
  if (from == 2 && to == 4) return 4;
  return 3;
}

void solve() {
  vector<int> order;
  vector<vector<int>> dp(5, vector<int>(5, INF));
  dp[0][0] = 0;

  while (true) {
    int nxt;
    scanf("%d", &nxt);
    if (nxt == 0) {
      break;
    }

    vector<vector<int>> tmp(5, vector<int>(5, INF));
    for (int prevL = 0; prevL < 5; ++prevL) {
      for (int prevR = 0; prevR < 5; ++prevR) {
        if (prevR != nxt) {
          // move left foot
          tmp[nxt][prevR] = min(tmp[nxt][prevR], dp[prevL][prevR] + cost(prevL, nxt));
        }
        if (prevL != nxt) {
          // move right foot
          tmp[prevL][nxt] = min(tmp[prevL][nxt], dp[prevL][prevR] + cost(prevR, nxt));
        }
      }
    }
    tmp.swap(dp);
  }

  int ans = INF;
  for (int l = 0; l < 5; ++l) {
    for (int r = 0; r < 5; ++r) {
      if (l != r) 
        ans = min(ans, dp[l][r]);
    }
  }

  printf("%d\n", ans != INF ? ans : 0);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
