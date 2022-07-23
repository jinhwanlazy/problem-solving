#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  scanf("%d", &N);

  set<int> negs;
  vector<int> K(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &K[i]);
    if (K[i] < 0) {
      negs.insert(i);
    }
  }
  
  int count = 0;
  while (!negs.empty()) {
    set<int> negsSwap;
    for (int i : negs) {
      if (K[i] >= 0) continue;
      K[i] *= -1;
      int nxt = (i == N-1 ? 0 : i+1);
      int prv = (i == 0 ? N-1 : i-1);
      K[nxt] -= K[i];
      K[prv] -= K[i];
      if (K[nxt] < 0) negsSwap.insert(nxt);
      if (K[prv] < 0) negsSwap.insert(prv);
      count++;
    }

    negsSwap.swap(negs);
  }
  
  printf("%d\n", count);

  return 0;
}
