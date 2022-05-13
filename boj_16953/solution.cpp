#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, K;
  scanf("%d %d", &N, &K);

  unordered_set<int> visited;
  unordered_set<int> locs{K};
  for (int count = 1; !locs.empty(); count++) {
    if (locs.find(N) != locs.end()) {
      printf("%d\n", count);
      return 0;
    }
    unordered_set<int> locs2;
    for (auto i : locs) {
      visited.insert(i);
    }
    for (auto i : locs) {
      if (i % 10 == 1 && i / 10 >= N && visited.find(i / 10) == visited.end()) {
        locs2.insert(i / 10);
      }
      if (i % 2 == 0 && i / 2 >= N && visited.find(i / 2) == visited.end()) {
        locs2.insert(i / 2);
      }
    }
    locs.swap(locs2);
  }
  printf("-1\n");
  return 0;
}
