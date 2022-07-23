#include <bits/stdc++.h>
using namespace std;

int main() {

  int N, L;
  scanf("%d %d", &N, &L);

  deque<pair<int, int>> dq;
  stringstream ss;

  for (int i = 0; i < N; ++i) {
    int x;
    scanf("%d", &x);

    while (!dq.empty() && dq.back().first > x) {
      dq.pop_back();
    }
    while (!dq.empty() && dq.front().second < i - L + 1) {
      dq.pop_front();
    }
    dq.push_back({x, i});

    ss << dq.front().first << " ";
  }
  printf("%s\n", ss.str().c_str());
  return 0;
}
