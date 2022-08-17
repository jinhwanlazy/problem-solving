#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N;
  scanf("%d", &N);
  
  vector<vector<char>> canvas(2 * N, vector<char>(N, ' '));
  for (int i = 0; i < 2*N; ++i) {
    for (int j = 0; j < N; ++j) {
      if ((i + j) % 2 == 0) {
        canvas[i][j] = '*';
      }
    }
  }
  for (int i = 0; i < canvas.size(); ++i) {
    cout << string(canvas[i].begin(), canvas[i].end()) << "\n";
  }
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
