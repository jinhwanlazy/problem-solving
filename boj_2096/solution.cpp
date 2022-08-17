#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N;
  scanf("%d", &N);

  int minDp[3], maxDp[3], tmp[3];

  for (int i = 0; i < N; ++i) {
    int A, B, C;
    scanf("%d %d %d", &A, &B, &C);
    if (i == 0) {
      minDp[0] = maxDp[0] = A;
      minDp[1] = maxDp[1] = B;
      minDp[2] = maxDp[2] = C;
    }
    else {
      tmp[0] = A + min(minDp[0], minDp[1]);
      tmp[1] = B + min({minDp[0], minDp[1], minDp[2]});
      tmp[2] = C + min(minDp[1], minDp[2]);
      memcpy(minDp, tmp, 3 * sizeof(int));
      tmp[0] = A + max(maxDp[0], maxDp[1]);
      tmp[1] = B + max({maxDp[0], maxDp[1], maxDp[2]});
      tmp[2] = C + max(maxDp[1], maxDp[2]);
      memcpy(maxDp, tmp, 3 * sizeof(int));
    }
  }
  int minAns = min({minDp[0], minDp[1], minDp[2]});
  int maxAns = max({maxDp[0], maxDp[1], maxDp[2]});
  
  printf("%d %d\n", maxAns, minAns);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
