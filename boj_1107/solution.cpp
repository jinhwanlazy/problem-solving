#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  scanf("%d", &N);

  int M;
  scanf("%d", &M);

  set<int> buttons{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (int i = 0; i < M; ++i) {
    int b;
    scanf("%d", &b);
    buttons.erase(b);
  }

  // for (int b : buttons) {
  // printf("%d ", b);
  //}
  // printf("\n");

  vector<int> channels(buttons.begin(), buttons.end());
  int ans = abs(N - 100);

  for (int i = 1; !channels.empty(); ++i) {
    vector<int> channels_swap;
    for (int ch : channels) {
      ans = min(ans, abs(N - ch) + i);
      if (ch != 0) {
        for (int b : buttons) {
          int nxt = ch * 10 + b;
          if (nxt <= 1000000) {
            channels_swap.push_back(nxt);
          }
        }
      }
    }
    channels.swap(channels_swap);
  }

  printf("%d\n", ans);

  return 0;
}
