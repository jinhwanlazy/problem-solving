#include <bits/stdc++.h>
using namespace std;
using LL = long long;

void solve() {
  int N, D;
  scanf("%d %d", &N, &D);

  vector<LL> S(D);
  for (int i = 0; i < N; ++i) {
    if (i < D) {
      scanf("%lld", &S[i]);
    }
    else {
      LL tmp;
      scanf("%lld", &tmp);
    }
  }

  vector<LL> P(N);
  for (int i = 0; i < N; ++i) {
    scanf("%lld", &P[i]);
  }
  sort(P.begin(), P.end());
  
  LL x = S.back() + P.back();
  S.pop_back();
  P.pop_back();

  multiset<LL> P_set;
  for (auto p : P) {
    P_set.insert(-p);
  }
  
  while (!S.empty()) {
   LL diff = x - S.back();
    if (diff < 0) {
      break;
    }
    auto it = P_set.lower_bound(-diff);
    if (it == P_set.end()) {
      break;
    }
    S.pop_back();
    P_set.erase(it);
  }

  printf("%lu\n", S.size() + 1);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
