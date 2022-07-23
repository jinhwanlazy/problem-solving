#include <bits/stdc++.h>
using namespace std;

using LL = long long;

int main() {
  int T;
  scanf("%d", &T);
  
  for (int t = 1; t <= T; ++t) {
    int N;
    scanf("%d", &N);
    
    vector<int> xs(N);
    for (int i = 0; i < N; ++i) {
      scanf("%d", &xs[i]);
    }
    
    LL ans = 0;
    int l = 0; 
    while (l < N) {
      int maxInd = max_element(xs.begin()+l, xs.end()) - xs.begin();
      for (int i = l; i < maxInd; ++i) {
        ans += LL(xs[maxInd] - xs[i]);
      }
      l = maxInd + 1;
    }
    printf("#%d %lld\n", t, ans);
  }

  return 0;
}
