#include <bits/stdc++.h>
using namespace std;

using LL = long long;

void solve() {
  LL T;
  scanf("%lld", &T);

  int N;
  scanf("%d", &N);

  vector<LL> A(N);
  for (int i = 0; i < N; ++i) {
    scanf("%lld", &A[i]);
  }

  int M;
  scanf("%d", &M);

  vector<LL> B(M);
  for (int i = 0; i < M; ++i) {
    scanf("%lld", &B[i]);
  }

  vector<LL> accA(N+1, 0), accB(M+1, 0);
  for (int i = 1; i <= N; ++i) {
    accA[i] = accA[i-1] + A[i-1];
  }

  for (int i = 1; i <= M; ++i) {
    accB[i] = accB[i-1] + B[i-1];
  }


  unordered_map<LL, LL> dictA, dictB;

  for (int i = 0; i < N; ++i) {
    for (int j = i+1; j <= N; ++j) {
      LL s = accA[j] - accA[i];
      dictA[s]++;
    }
  }

  for (int i = 0; i < M; ++i) {
    for (int j = i+1; j <= M; ++j) {
      LL s = accB[j] - accB[i];
      dictB[s]++;
    }
  }

  LL ans = 0;
  for (const auto& [a, i] : dictA) {
    LL b = T - a;
    auto it = dictB.find(b);
    if (it != dictB.end()) {
      ans += i * it->second;
    }
  }
  
  printf("%lld\n", ans);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
