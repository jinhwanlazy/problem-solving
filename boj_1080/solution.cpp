#include <bits/stdc++.h>
using namespace std;

void readMat(int N, int M, vector<vector<int>>& mat) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      char c;
      scanf(" %c", &c);
      mat[i][j] = c == '1';
    }
  }
}

void op(vector<vector<int>>& mat, int i, int j) {
  for (int di = 0; di < 3; ++di) {
    for (int dj = 0; dj < 3; ++dj) {
      mat[i + di][j + dj] ^= 1;
    }
  }
}

void solve() {
  int N, M;
  scanf("%d %d", &N, &M);

  vector<vector<int>> A(N, vector<int>(M));
  vector<vector<int>> B(N, vector<int>(M));
  readMat(N, M, A);
  readMat(N, M, B);
  int count = 0;
  for (int i = 0; i < N - 2; ++i) {
    for (int j = 0; j < M - 2; ++j) {
      if (A[i][j] != B[i][j]) {
        op(A, i, j);
        count++;
      }
    }
  }
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      if (A[i][j] != B[i][j]) {
        printf("%d\n", -1);
        return;
      }
    }
  }
  printf("%d\n", count);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
