#include <bits/stdc++.h>
using namespace std;

void solve() {
  int ans = 0;
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      char c;
      scanf(" %c", &c);
      if ((i + j) % 2 == 0) {
        ans += c == 'F';
      }
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
