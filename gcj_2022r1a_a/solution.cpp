#include <bits/stdc++.h>
using namespace std;

string solution() {
  string s;
  cin >> s;
  stringstream ss;
  for (int i = 0; i < s.size(); ++i) {
    char c = s[i];
    ss << c;
    int j = i + 1;
    while (j < s.size() && s[j] == c) {
      j++;
    }
    if (j < s.size() && s[j] > c) {
      ss << c;
    }
  }
  return ss.str();
}

int main() {
  int T;
  cin >> T;
  for (int i = 1; i <= T; ++i) {
    cout << "Case #" << i << ": " << solution() << "\n";
  }
  return 0;
}
