#include <bits/stdc++.h>
using namespace std;

void solve() {
  string s;
  cin >> s;
  
  int ans = 0;
  //stack<char> st;
  stack<int> st;
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] == '(') {
      st.push(i);
    }
    else {
      if (st.top() == i-1) {
        ans += st.size()-1;
      }
      else {
        ans += 1;
      }
      st.pop();
    }
  }
  ans += st.size();
  
  printf("%d\n", ans);
  
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
