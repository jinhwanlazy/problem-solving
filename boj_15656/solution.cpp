#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, M;
  scanf("%d %d", &N, &M);

  vector<int> xs(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &xs[i]);
  }
  
  sort(xs.begin(), xs.end());

  stack<vector<int>> S;
  for (int i = N-1; i >= 0; --i) {
    S.push({i});
  }

  while (!S.empty()) {
    auto inds = S.top(); S.pop();
    if (inds.size() == M) {
      for (int i : inds) {
        printf("%d ", xs[i]);
      }
      printf("\n");
      continue;
    }
    for (int i = N-1; i >= 0; --i) {
      inds.push_back(i);
      S.push(inds);
      inds.pop_back();
    }
  }
  
  return 0;
}


