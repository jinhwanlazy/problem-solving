#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  scanf("%d", &T);

  while (T--) {
    int M, N, x, y;
    scanf("%d %d %d %d", &M, &N, &x, &y);
    x--;
    y--;

    unordered_set<int> A;
    unordered_set<int> B;

    int max_year = M * N;
    for (int i = 0; i + x < max_year; i += M) {
      A.insert(i+x);
    }
    for (int i = 0; i + y < max_year; i += N) {
      B.insert(i+y);
    }

    unordered_set<int> C;
    for (int a : A) {
      if (B.find(a) != B.end()) {
        C.insert(a);
      }
    }
    if (C.empty()) {
      printf("-1\n");
    }
    else {
      printf("%d\n", *C.begin() + 1);
    }
  }

  return 0;
}
