#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N;
  scanf("%d", &N);

  vector<int> xs(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &xs[i]);
  }

  //sort(xs.begin(), xs.end());
  
  auto l = xs.begin();
  auto r = xs.end() - 1;
  auto ansL = l;
  auto ansR = r;
  while (l < r) {
    int m = *l + *r;
    //printf("%d %d\n", *l, *r);
    if (abs(m) <= abs(*ansL + *ansR)) {
      ansL = l;
      ansR = r;
    }
    if (m <= 0) {
      l++;
    }
    else {
      r--;
    }
  }
  printf("%d %d\n", *ansL, *ansR);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
