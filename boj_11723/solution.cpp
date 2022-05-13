#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(NULL);
  ios::sync_with_stdio(false);

  int N;
  cin >> N;

  int mask = 0;
  for (int i = 0; i < N; ++i) {
    string cmd;
    cin >> cmd;
    int x;
    if (cmd == "add") {
      cin >> x;
      mask |= 1 << x;
    }
    if (cmd == "check") {
      cin >> x;
      cout << ((mask >> x) & 1) << "\n";
    }
    if (cmd == "remove") {
      cin >> x;
      mask &= ~(1 << x);
    }
    if (cmd == "toggle") {
      cin >> x;
      mask ^= (1 << x);
    }
    if (cmd == "all") {
      mask = (1 << 21) - 1;
    }
    if (cmd == "empty") {
      mask = 0;
    }
  }

  return 0;
}
