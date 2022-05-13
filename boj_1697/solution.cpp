#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, K;
  scanf("%d %d", &N, &K);

  unordered_set<int> visited;
  unordered_set<int> locs{N};
  for (int count = 0;; count++) {
    if (locs.find(K) != locs.end()) {
      printf("%d\n", count);
      return 0;
    }
    unordered_set<int> locs2;
    for (auto i : locs) {
      visited.insert(i);
    }
    for (auto i : locs) {
      if (visited.find(i + 1) == visited.end()) {
        locs2.insert(i + 1);
      }
      if (i > 0 && visited.find(i - 1) == visited.end()) {
        locs2.insert(i - 1);
      }
      if (i < K && visited.find(i * 2) == visited.end()) {
        locs2.insert(i * 2);
      }
    }
    locs.swap(locs2);
  }
  return 0;
}
