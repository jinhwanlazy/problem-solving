#include <bits/stdc++.h>
using namespace std;

constexpr static int INF = numeric_limits<int>::max() / 2;


void solve() {
  int N;
  scanf("%d", &N);

  int xMax = -INF, xMin = INF;
  int yMax = -INF, yMin = INF;

  for (int i = 0; i < N; ++i) {
    int x, y;
    scanf("%d %d", &x, &y);
    xMax = max(x, xMax);
    xMin = min(x, xMin);
    yMax = max(y, yMax);
    yMin = min(y, yMin);
  }
  int ans = 0;
  if (xMax > 0) ans += xMax;
  if (xMin < 0) ans += -xMin;
  if (yMax > 0) ans += yMax;
  if (yMin < 0) ans += -yMin;
  ans *= 2;
  printf("%d\n", ans);
}

int main() {
  int T;
  scanf("%d", &T);
  
  while (T--) {
    solve();
  }

  return 0;
}
