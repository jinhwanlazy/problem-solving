#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

void solve() {
  int N;
  scanf("%d", &N);

  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &A[i]);
  }

  sort(A.begin(), A.end());
  
  int ans = 0;
  do {
    int tmp = 0;
    for (int i = 0; i < N-1; ++i) {
      tmp += abs(A[i] - A[i+1]);
    }
    ans = max(ans, tmp);
  } while (next_permutation(A.begin(), A.end()));
  printf("%d\n", ans);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
