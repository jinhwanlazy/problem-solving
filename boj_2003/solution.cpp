#include <bits/stdc++.h>
using namespace std;

using LL = long long;

void solve() {
  int N, M;
  scanf("%d %d", &N, &M);

  deque<LL> xs;
  LL sum = 0;
  int count = 0;
  for (int i = 0; i < N; ++i) {
    LL x;
    scanf("%lld", &x);

    sum += x;
    xs.push_back(x);
    
    while (!xs.empty() && sum > M) {
      sum -= xs.front();
      xs.pop_front();
    }

    if (sum == M) {
      count++;
    }
  }
  printf("%d\n", count);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
