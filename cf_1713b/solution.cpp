#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N;
  scanf("%d", &N);

  vector<int> xs(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &xs[i]);
  }

  int countMaxima = 0;
  //int maxX = *max_element(xs.begin(), xs.end());
  for (int i = 0; i < N;) {
    if (i > 0 && xs[i-1] >= xs[i]) {
      ++i;
      continue;
    }
    int j = i;
    while (j < N && xs[j] == xs[i]) {
      j++;
    }
    if (j == N || xs[i] > xs[j]) {
      countMaxima++;
    }
    i = j;
  }
  
  if (countMaxima == 1) {
    printf("YES\n");
  }
  else {
    printf("NO\n");
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
