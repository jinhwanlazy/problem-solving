#include <bits/stdc++.h>
using namespace std;

int LCS(const string& A, const string& B, string* trace = nullptr) {
  /*
   * dp[i][j] := LCS(A[:i], B[:j])
   */
  vector<vector<int>> dp(A.size() + 1, vector<int>(B.size() + 1, 0));
  for (int i = 1; i <= A.size(); ++i) {
    for (int j = 1; j <= B.size(); ++j) {
      if (A[i - 1] == B[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
      }
    }
  }

  if (trace != nullptr) {
    int i = A.size();
    int j = B.size();
    trace->clear();
    while (i > 0 && j > 0) {
      if (A[i - 1] == B[j - 1]) {
        trace->push_back(A[i - 1]);
        i--;
        j--;
      } else if (dp[i - 1][j] == dp[i][j]) {
        i--;
      } else if (dp[i][j - 1] == dp[i][j]) {
        j--;
      }
    }
    reverse(trace->begin(), trace->end());
  }
  return dp.back().back();
}

int main() {
  string A, B, ans;
  cin >> A >> B;

  cout << LCS(A, B, &ans) << "\n";
  cout << ans << "\n";
  return 0;
}
