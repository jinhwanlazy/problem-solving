#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N;
  cin >> N;

  vector<int> xs(N);
  for (int i = 0; i < N; ++i) {
    cin >> xs[i];
  }

  nth_element(xs.begin(), xs.begin() + (N - 1) / 2, xs.end());
  cout << xs[(N-1)/2] << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
