#include <bits/stdc++.h>
using namespace std;

using LL = long long;
using LD = long double;

int main() {
  int N, M;
  scanf("%d %d", &N, &M);

  vector<int> ms(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &ms[i]);
  }

  vector<int> cs(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &cs[i]);
  }

  /*
   * dp[accumulated_cost] := accumulated_cost 일때의 비워지는 최대 메모리
   */
  unordered_map<int, int> dp;
  dp.insert({0, 0});
  for (int i = 0; i < N; ++i) {
    auto dp2(dp);
    int m = ms[i];
    int c = cs[i];
    for (const auto& pair : dp) {
      int c_acc = pair.first + c;
      int m_acc = pair.second + m;
      auto it = dp2.find(c_acc);
      if (it != dp2.end()) {
        it->second = max(it->second, m_acc);
      } else {
        dp2.insert({c_acc, m_acc});
      }
    }
    dp.swap(dp2);
  }
  int ans = numeric_limits<int>::max();
  for (const auto& p : dp) {
    if (p.second >= M) {
      ans = min(ans, p.first);
    }
  }
  printf("%d\n", ans);
  return 0;
}
