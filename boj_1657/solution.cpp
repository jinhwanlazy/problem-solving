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


int price(char a, char b) {
  if (a == 'F') a--;
  if (b == 'F') b--;
  static const int price_[5][5] = {
    {10, 8, 7, 5, 1},
    {8, 6, 4, 3, 1},
    {7, 4, 3, 2, 1},
    {5, 3, 2, 2, 1},
    {1, 1, 1, 1, 0},
  };
  return price_[a - 'A'][b - 'A'];
}

int main() {
  int N, M;
  scanf("%d %d", &N, &M);

  vector<vector<char>> tofu(N, vector<char>(M));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      scanf(" %c", &tofu[i][j]);
    }
  }

  unordered_map<Key, int> dp, tmp;
  dp.insert({Key(), 0});
  tmp.insert({Key(), 0});
  while (!tmp.empty()) {
    unordered_map<Key, int> nxt;
    for (auto [key_, val] : tmp) {
      int i, j;
      Key key(key_);
      if (!findFirstEmpty(key, i, j, N, M)) {
        continue;
      }
      key.set(size_t(M*i + j));
      nxt[key] = max(nxt[key], val);
      if (j < M-1 && !key.test(M*i+j+1)) {
        key.set(M*i+j+1);
        nxt[key] = max(nxt[key], val + price(tofu[i][j], tofu[i][j+1]));
        key.reset(M*i+j+1);
      }
      if (i < N-1 && !key.test(M*i+j+M)) {
        key.set(M*i+j+M);
        nxt[key] = max(nxt[key], val + price(tofu[i][j], tofu[i+1][j]));
        key.reset(M*i+j+M);
      }
    }
    tmp.swap(nxt);
    for (const auto& [key, val] : tmp) {
      dp[key] = max(dp[key], val);
    }
  }
  
  int ans = 0;
  ans = dp[Key().set()];
  for (const auto& [key, val] : dp) {
    ans = max(ans, val);
    //printf("%d\n", val);
    //printKey(key, N, M);
  }
  printf("%d\n", ans);

  return 0;
}

