#include <bits/stdc++.h>
using namespace std;

void solve() {
  int n, k, x;
  scanf("%d %d %d", &n, &k, &x);

  vector<int> A(1024, 0);

  for (int i = 0; i < n; ++i) {
    int a;
    scanf("%d", &a);
    A[a]++;
  }

  while (k--) {
    vector<int> ASwap(1024, 0);
    int processed = 0;
    for (int i = 0; i < A.size(); ++i) {
      if (processed % 2 == 0) {
        ASwap[i^x] += (A[i] + 1) / 2;
        ASwap[i] += A[i] - (A[i] + 1) / 2;
      }
      else {
        ASwap[i] += (A[i] + 1) / 2;
        ASwap[i^x] += A[i] - (A[i] + 1) / 2;
      }
      processed += A[i];
    }
    A.swap(ASwap);
  }
  
  int maxA = numeric_limits<int>::min();
  int minA = numeric_limits<int>::max();
  for (int i = 0; i < A.size(); ++i) {
    if (A[i]) {
      minA = min(minA, i);
      maxA = max(maxA, i);
    }
  }

  printf("%d %d\n", maxA, minA);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
