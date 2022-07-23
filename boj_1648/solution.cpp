#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;
using LL = long long;

using Key = bitset<196>;

constexpr int MOD = 9901;

void printKey(const Key& key, int N, int M) {
  for (int i = 0; i < N; ++i) {
    for(int j = 0; j < M; ++j) {
      cout << int(key.test(M*i+j));
    }
    cout << "\n";
  }
}

bool findFirstEmpty(const Key& key, int& i, int& j, int N, int M) {
  for (i = 0; i < N; ++i) {
    for (j = 0; j < M; ++j) {
      if (!key.test(M*i+j)) {
        return true;
      }
    }
  }
  return false;
}

int main() {
  int N, M;
  scanf("%d %d", &N, &M);

  if ((M * N) & 1) {
    printf("0\n");
    return 0;
  }

  unordered_map<Key, int> dp;
  dp.insert({Key(), 1});
  
  for (int k = 0; k * 2 < M * N; ++k) {
    unordered_map<Key, int> nxt;
    for (auto [key_, cnt] : dp) {
      int i, j;
      Key key(key_);
      if (!findFirstEmpty(key, i, j, N, M)) {
        continue;
      }
      key.set(size_t(M*i + j));
      if (j < M-1 && !key.test(M*i+j+1)) {
        key.set(M*i+j+1);
        nxt[key] += cnt;
        nxt[key] %= MOD;
        key.reset(M*i+j+1);
      }
      if (i < N-1 && !key.test(M*i+j+M)) {
        key.set(M*i+j+M);
        nxt[key] += cnt;
        nxt[key] %= MOD;
        key.reset(M*i+j+M);
      }
    }
    dp.swap(nxt);
  }

  int ans = dp.begin()->second;
  printf("%d\n", ans);

  return 0;
}
