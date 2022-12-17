#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N, K;
  scanf("%d %d", &N, &K);

  list<char> lst;
  for (int i = 0; i < N; ++i) {
    char c;
    scanf(" %c", &c);
    lst.push_back(c);
  }

  auto it = lst.begin();
  while (K--) {
    for (; next(it) != lst.end() && *it >= *next(it); ++it) {}
    if (it == lst.begin()) {
      lst.erase(it);
      it = lst.begin();
    }
    else {
      lst.erase(it--);
    }
  }

  for (const char& c : lst) {
    printf("%c", c);
  }
  printf("\n");
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
