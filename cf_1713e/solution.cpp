#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N;
  scanf("%d", &N);

  vector<vector<int>> M(N, vector<int>(N));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      scanf("%d", &M[i][j]);
    }
  }

  auto swap = [&](int k) {
    for (int i = 0; i < N; ++i) {
      if (i == k) 
        continue;
      std::swap(M[i][k], M[k][i]);
    }
  };
  

  for (int k = 0; k < N; ++k) {
    for (int i = 0; i < N; ++i) {
      if (i == k) {
        continue;
      }
      if (M[i][k] == M[k][i]) {
        continue;
      }
      int v = N * i + k;
      int h = N * k + i;
      if (v > h && M[i][k] < M[k][i]) {
        swap(k);
      }
      if (v < h && M[i][k] > M[k][i]) {
        swap(k);
      }
      break;
    }
  }

  for (int i = 0; i < M.size(); ++i) {
    for(int j = 0; j < M[i].size(); ++j) {
      printf("%d ", M[i][j]);
    }
    printf("\n");
  }
}

int main() {
  int T;
  scanf("%d", &T);
  
  while (T--) {
    solve();
  }

  return 0;
}
