#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;

  vector<vector<int>> S(N, vector<int>(N, 0));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      scanf("%d", &S[i][j]);
    }
  }

  vector<int> div(N, 0);
  for (int i = N / 2; i < N; ++i) {
    div[i] = 1;
  }
  int min_score_diff = numeric_limits<int>::max();
  do {
    int scores[2] = {0};
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        if (div[i] == div[j]) {
          scores[div[i]] += S[i][j];
        }
      }
    }
    min_score_diff = min(min_score_diff, abs(scores[0] - scores[1]));
  } while (next_permutation(div.begin(), div.end()));
  cout << min_score_diff << "\n";
  return 0;
}
