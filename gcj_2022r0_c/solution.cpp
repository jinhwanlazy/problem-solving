#include <bits/stdc++.h>
using namespace std;

int solution() {
  int N;
  cin >> N;
  multiset<int> dice;
  for (int i = 0; i < N; ++i) {
    int d;
    cin >> d;
    dice.insert(d);
  }

  int i = 0;
  for (; i < N; ++i) {
    auto it = dice.lower_bound(i + 1);
    if (it == dice.end()) {
      break;
    }
    dice.erase(it);
  }
  return i;
}

int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    cout << "Case #" << t << ": ";
    cout << solution() << "\n";
  }
  return 0;
}
