#include <bits/stdc++.h>
using namespace std;

using LL = long long;

int main() {
  int T;
  scanf("%d", &T);

  while (T--) {
    LL M, N, x, y;
    scanf("%lld %lld %lld %lld", &M, &N, &x, &y);
    x--;
    y--;
    if (M < N) {
      swap(M, N);
      swap(x, y);
    }

    bool good = false;
    LL cand = x;
    while (cand < M * N) {
      if (cand % N == y) {
        good = true;
        break;
      }
      cand += M;
    }
    if (good) {
      printf("%lld\n", cand+1);
    }
    else {
      printf("-1\n");
    }
  }
  return 0;
}
