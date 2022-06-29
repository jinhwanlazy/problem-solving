#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main() {
  int N;
  scanf("%d", &N);
  if (N < 2) {
    printf("0\n");
    return 0;
  }
  if (N & 1) { // N cannot be odd
    printf("0\n");
    return 0;
  }
  N /= 2; 

  // dp[i] := 2*i 까지의 벽을 채우는 경우의 수
  vector<int> dp(N+1, 0);
  dp[0] = 1;
  dp[1] = 3;
  for (int i = 2; i <= N; ++i) {
    //dp[i] = dp[i-1];
    //for (int j = 0; j < i; ++j) {
      //dp[i] += 2 * dp[j];
    //}
    dp[i] = 4 * dp[i-1] - dp[i-2];
  }

  printf("%d\n", dp[N]);

  return 0;
}
