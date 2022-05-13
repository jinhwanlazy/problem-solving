#include <bits/stdc++.h>
using namespace std;

int main() {
  int G, P;
  scanf("%d %d", &G, &P);

  set<int> remaining_gates;
  for (int i = 1; i <= G; ++i) {
    remaining_gates.insert(i);
  }

  vector<int> gs(P);
  for (int i = 0; i < P; ++i) {
    scanf("%d", &gs[i]);
  }

  int count = 0;
  for (int g : gs) {
    if (remaining_gates.empty()) {
      break;
    }
    auto it = remaining_gates.lower_bound(g);
    if (it == remaining_gates.end()) {
      it--;
    }
    while (it != remaining_gates.begin() && *it > g) {
      it--;
    }
    if (it != remaining_gates.end() && *it <= g) {
      remaining_gates.erase(it);
      count++;
    } else {
      break;
    }
  }

  cout << count << "\n";

  return 0;
}
