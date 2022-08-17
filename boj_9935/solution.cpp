#include <bits/stdc++.h>
using namespace std;

void solve() {
  string input;
  cin >> input;

  string bomb;
  cin >> bomb;

  vector<char> res;
  vector<int> prefixMatches;
  res.reserve(input.size());
  prefixMatches.reserve(input.size());

  for (char c : input) {
    res.push_back(c);
    if (res.size() >= bomb.size()) {
      bool match = true;
      auto it = res.end() - bomb.size();
      for (int i = 0; i < bomb.size(); ++i, ++it) {
        if (bomb[i] != *it) {
          match = false;
          break;
        }
      }
      if (match) {
        for (int i = 0; i < bomb.size(); ++i) {
          res.pop_back();
        }
      }
    }
  }

  string ans(res.begin(), res.end());
  if (ans.empty()) {
    printf("FRULA\n");
  }
  else {
    printf("%s\n", ans.c_str());
  }
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
