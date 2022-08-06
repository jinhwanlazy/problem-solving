#include <bits/stdc++.h>
using namespace std;

void solve() {
  unsigned long N;
  scanf("%lu", &N);
  unsigned i = 1;
  for (; 2 * i + 1 <= N; ++i) {
    N -= i;
  }
  printf("%d\n", i);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
