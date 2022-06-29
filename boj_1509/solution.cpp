#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;
using LL = long long;
constexpr static int INF = numeric_limits<int>::max();

int main() {
  string S;
  cin >> S;

  vector<vector<bool>> isPalindrom(S.size(), vector<bool>(S.size(), false));
  for (int i = 0; i < S.size(); ++i) {
    isPalindrom[i][i] = true;
  }
  for (int i = 0; i < S.size()-1; ++i) {
    int j = i + 1;
    isPalindrom[i][j] = S[i] == S[j];
  }
  for (int step = 2; step < S.size(); ++step) {
    for (int i = 0; i + step < S.size(); ++i) {
      int j = i + step;
      isPalindrom[i][j] = (S[i] == S[j]) && isPalindrom[i+1][j-1];
    }
  }
  
  // dp[i] := [0, i] 구간에서의 palindrom 최소 분할
  vector<int> dp(S.size(), INF);
  dp[0] = 1;
  for (int i = 1; i < S.size(); ++i) {
    if (isPalindrom[0][i]) {
      dp[i] = 1;
      continue;
    }
    for (int s = 1; s <= i; ++s) {
      if (isPalindrom[s][i]) {
        dp[i] = min(dp[i], dp[s-1] + 1);
      }
    }
  }

  int ans = dp[S.size()-1];
  printf("%d\n", ans);
  return 0;
}
