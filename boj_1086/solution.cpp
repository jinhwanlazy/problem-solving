#include <bits/stdc++.h>
using namespace std;

using LL = long long;

int get_rem(const string& num, int K) {
  int res = 0;
  for (char c : num) {
    res = (res * 10 + (c - '0')) % K;
  }
  return res;
}

int get_digit_rem(const string& num, int K) {
  int res = 1;
  for (int i = 0; i < num.size(); ++i) {
    res = (res * 10) % K;
  }
  return res;
}

int main() {
  int N;
  scanf("%d", &N);

  vector<string> inputs(N);
  for (int i = 0; i < N; ++i) {
    cin >> inputs[i];
  }
  int K;
  scanf("%d", &K);

  vector<int> rems(N);
  vector<int> digit_rems(N);
  for (int i = 0; i < N; ++i) {
    rems[i] = get_rem(inputs[i], K);
    digit_rems[i] = get_digit_rem(inputs[i], K);
  }

  /*  dp[mask][rem] := mask 에 해당하는 숫자들로에서 얻어지는 나머지가 rem인
   *  조합의 갯수.
   */
  vector<vector<LL>> dp(1 << N, vector<LL>(K, 0));
  unordered_set<int> masks;
  for (int i = 0; i < N; ++i) {
    int mask = 1 << i;
    dp[mask][rems[i]] = 1;
    masks.insert(mask);
  }
  while (!masks.empty()) {
    unordered_set<int> masks_swap;
    for (int mask : masks) {
      for (int i = 0; i < N; ++i) {
        if ((mask >> i) & 1) {
          continue;
        }
        int new_mask = mask | (1 << i);
        for (int rem = 0; rem < K; ++rem) {
          int new_rem = (rem * digit_rems[i] + rems[i]) % K;
          dp[new_mask][new_rem] += dp[mask][rem];
        }
        masks_swap.insert(new_mask);
      }
    }
    masks.swap(masks_swap);
  }
  LL num = dp[(1 << N) - 1][0];
  LL denom = 0;
  for (LL r : dp[(1 << N) - 1]) {
    denom += r;
  }
  LL d = gcd(num, denom);
  cout << num / d << "/" << denom / d << "\n";
  return 0;
}
