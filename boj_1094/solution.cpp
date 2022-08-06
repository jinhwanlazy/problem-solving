#include <bits/stdc++.h>
using namespace std;

void solve() {
  int X;
  scanf("%d", &X);

  int ans = 0;
  while (X) {
    ans += X & 1;
    X >>= 1;
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
