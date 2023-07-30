#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N;
  scanf("%d", &N);

  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &A[i]);
  }

  string S;
  cin >> S;

  vector<int> acc(N+1, 0);
  for (int i = 0; i < N; ++i) {
    acc[i+1] = acc[i] + A[i];
  }

  int ans = 0;
  int tmp = 0;
  for (int i = N-1; i >= 0; --i) {
    if (S[i] == '1') {
      ans = max(ans, tmp + acc[i]);
      tmp += A[i];
      ans = max(ans, tmp);
    }
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
