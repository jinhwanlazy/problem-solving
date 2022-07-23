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

  stack<pair<vector<int>, unordered_set<int>>> S;
  for (int i = N-1; i >= 0; --i) {
    S.push({{i}, {i}});
  }

  while (!S.empty()) {
    auto [sequence, in] = S.top(); S.pop();
    if (sequence.size() == M) {
      for (int i : sequence) {
        printf("%d ", xs[i]);
      }
      printf("\n");
      continue;
    }
    for (int i = N-1; i >= sequence.back(); --i) {
      if (!in.count(i)) {
        sequence.push_back(i);
        in.insert(i);
        S.push({sequence, in});
        sequence.pop_back();
        in.erase(i);
      }
    }
  }
  
  return 0;
}

