#include <bits/stdc++.h>
using namespace std;

void solve() {
  string w;
  cin >> w;
  if (w.size() <= 10) {
    cout << w << "\n";
  }
  else {
    cout << w.front();
    cout << w.size() - 2;
    cout << w.back() << "\n";
  }
}

int main() {
  int T;
  scanf("%d", &T);
  
  while (T--) {
    solve();
  }

  return 0;
}
