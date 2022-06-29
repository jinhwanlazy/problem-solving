#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;
using LL = long long;
constexpr static int INF = numeric_limits<int>::max();

int rotDown(int src, int dst) {
  if (src >= dst) {
    return src - dst;
  }
  return src - dst + 10;
}

int rotUp(int src, int dst) {
  if (dst >= src) {
    return dst - src;
  }
  return dst - src + 10;
}

int main() {
  int N;
  cin >> N;

  string src;
  string dst;
  cin >> src >> dst;

  // src 수열을 {0} 으로 맞추는 문제로 변형.
  for (int i = 0; i < N; ++i) {
    src[i] = (src[i] - dst[i] + 10) % 10;
  }

  // dp[i][k] := 숫자나사 [i, N) 구간을 똑같은 숫자 k로 만드는데 필요한 최소 회전수
  // trace[i][k] := 해당 위치에서 필요한 회전수 & i+1에서의 best k
  vector<vector<int>> dp(N, vector<int>(10, INF));
  vector<vector<pair<int, int>>> trace(N, vector<pair<int, int>>(10, {0, 0}));
  for (int k = 0; k < 10; ++k) {
    int d = rotDown(src[N-1], k);
    int u = rotUp(src[N-1], k);
    if (u > d) {
      dp[N-1][k] = d;
      trace[N-1][k] = {-d, INF};
    }
    else {
      dp[N-1][k] = u;
      trace[N-1][k] = {u, INF};
    }
  }
  for (int i = N-2; i >= 0; --i) {
    for (int k = 0; k < 10; ++k) {
      int cand;
      cand = dp[i + 1][k] + rotDown(src[i], k);
      if (cand < dp[i][k]) {
        dp[i][k] = cand;
        trace[i][k] = {-rotDown(src[i], k), k};
      }
      cand = dp[i + 1][src[i]] + rotUp(src[i], k);
      if (cand < dp[i][k]) {
        dp[i][k] = cand;
        trace[i][k] = {rotUp(src[i], k), src[i]};
      }
    }
  }

  int ans = dp[0][0];
  printf("%d\n", ans);

  auto [rot, k] = trace[0][0];
  printf("%d %d\n", 1, rot);
  for (int i = 1; i < N; ++i) {
    auto nxt = trace[i][k];
    rot = nxt.first;
    k = nxt.second;
    printf("%d %d\n", i+1, rot);
  }
  
  return 0;
}
