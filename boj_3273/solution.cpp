#include <bits/stdc++.h>
using namespace std;

using LL = long long;

int main() {
  int N;
  scanf("%d", &N);

  vector<LL> as(N);
  for (int i = 0; i < N; ++i) {
    scanf("%lld", &as[i]);
  }

  LL x;
  scanf("%lld", &x);

  sort(as.begin(), as.end());

  // for (int i = 0; i < as.size(); ++i) {
  // printf("%d ", as[i]);
  //}
  // printf("\n");
  LL count = 0;
  int l = 0, r = N - 1;
  while (l < r) {
    while (as[l] + as[r] > x) {
      r--;
    }
    if (as[l] + as[r] == x) {
      LL count_dup = 0;
      for (int rr = r; rr > l && as[r] == as[rr]; --rr) {
        count_dup++;
      }
      count += count_dup;
    }
    l++;
  }
  printf("%lld\n", count);

  return 0;
}
