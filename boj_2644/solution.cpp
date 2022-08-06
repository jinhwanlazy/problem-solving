#include <bits/stdc++.h>
using namespace std;

int findDepth(const vector<int>& parentOf, vector<int>& depthOf, int u) {
  int& res = depthOf[u];
  if (res != -1) {
    return res;
  }
  if (parentOf[u] == -1) {
    res = 0;
    return res;
  } 
  res = 1 + findDepth(parentOf, depthOf, parentOf[u]);
  return res;
}

void solve() {
  int N;
  scanf("%d", &N);

  int a, b;
  scanf("%d %d", &a, &b);

  int M;
  scanf("%d", &M);

  vector<int> parent(N+1, -1);
  for (int i = 0; i < N; ++i) {
    int p, c;
    scanf("%d %d", &p, &c);
    parent[c] = p;
  }

  vector<int> depth(N+1, -1);
  int ad = findDepth(parent, depth, a);
  int bd = findDepth(parent, depth, b);
  
  int count = 0;
  while (a != b) {
    if (ad > bd) {
      a = parent[a];
      ad--;
      count++;
    }
    else if (ad < bd) {
      b = parent[b];
      bd--;
      count++;
    }
    else {
      a = parent[a];
      b = parent[b];
      ad--;
      bd--;
      count += 2;
    }
    
  }
  if (a == -1 && b == -1) {
    printf("%d\n", -1);
  }
  else {
    printf("%d\n", count);
  }
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}

