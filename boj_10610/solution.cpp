#include <bits/stdc++.h>
using namespace std;

void solve() {
  string s;
  cin >> s;
  sort(s.begin(), s.end());
  
  int check = 0;
  for (char c : s) {
    check += c - '0';
  }

  if (check % 3 == 0 && s.front() == '0') {
    string ans(s.rbegin(), s.rend());
    cout << ans << "\n";
  }
  else {
    cout << "-1\n";
  }
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
