#include <bits/stdc++.h>
using namespace std;

int required_flip(const vector<string>& board, int start_row, int start_col) {
  int count1 = 0;
  int count2 = 0;
  for (int i = start_row; i < start_row + 8; ++i) {
    for (int j = start_col; j < start_col + 8; ++j) {
      count1 += board[i][j] != ((i + j) % 2 ? 'W' : 'B');
      count2 += board[i][j] != ((i + j) % 2 ? 'B' : 'W');
    }
  }
  return min(count1, count2);
}

int main() {
  int N, M;
  cin >> N >> M;

  vector<string> board(N);
  for (int i = 0; i < N; ++i) {
    cin >> board[i];
    // cout << board[i];
  }

  int ans = N * M;
  for (int i = 0; i <= N - 8; ++i) {
    for (int j = 0; j <= M - 8; ++j) {
      ans = min(ans, required_flip(board, i, j));
    }
  }
  cout << ans << "\n";
  return 0;
}
