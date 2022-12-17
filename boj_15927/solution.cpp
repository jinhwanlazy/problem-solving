#include <bits/stdc++.h>
using namespace std;

void solve() {
  string s;
  cin >> s;

  if (all_of(s.begin() + 1, s.end(),
             [&s](const char c) -> bool { return c == s[0]; })) {
    printf("%d\n", -1);
    return;
  }

  bool isPalindrome = true;
  for (int i = 0; i * 2 < s.size(); ++i) {
    if (s[i] != s[s.size()-i-1]) {
      isPalindrome = false;
      break;
    }
  }
  if (isPalindrome) {
    printf("%lu\n", s.size() - 1);
  } else {
    printf("%lu\n", s.size());
    
  }
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
