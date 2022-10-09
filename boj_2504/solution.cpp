#include <bits/stdc++.h>
using namespace std;

char oppositBracket(char closing) {
  switch (closing) {
   case ')': return '(';
   case ']': return '[';
   default: throw;
  }
}

int value(char closing) {
  switch (closing) {
   case ')': return 2;
   case ']': return 3;
   default: throw;
  }
}

void solve() {
  string input;
  cin >> input;
  
  stack<char> S;
  for (char c : input) {
    if (c == '(' || c == '[') {
      S.push(c);
      continue;
    }
    int x = 0;
    char o = oppositBracket(c);
    while (S.top() != o) {
      cout << S.top() << ", " << o << ", " << c << "\n";
      if (!isdigit(S.top())) {
        printf("0\n");
        return;
      }
      x += S.top();
      S.pop();
    }
    S.pop();
    S.push(value(c) * (x == 0 ? 1 : x));
  }
  
  int ans = 0;
  while (!S.empty()) {
    ans += S.top();
    S.pop();
  }
  printf("%d\n", ans);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
