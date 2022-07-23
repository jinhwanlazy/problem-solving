#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
  int N;
  scanf("%d", &N);
  
  vector<LL> C(N);
  for (int i = 0; i < N; ++i) {
    int a;
    scanf("%d", &a);
    C[i] += a;
  }

  for (int i = 0; i < N; ++i) {
    int b;
    scanf("%d", &b);
    C[i] -= b;
  }
  
  map<LL, int> cnt;
  LL sum = 0;
  LL res = 0;
  for (int i = 0; i < N; ++i) {
    sum += C[i];
    res += cnt[sum];
    if (sum == 0) {
      res += 1;
    }
    cnt[sum] += 1;
  }
  printf("%lld\n", res);
  

  return 0;
}
