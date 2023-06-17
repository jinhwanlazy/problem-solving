#include <bits/stdc++.h>
using namespace std;

void solve() {
  string keys;
  cin >> keys;

  list<char> buf;
  //buf.push_back('\n');
  auto it = buf.begin();
  
  for (const char key : keys) {
    switch (key) {
      case '<':
        if (it != buf.begin()) {
          it--;
        }
        break;
      case '>':
        if (it != --buf.end()) {
          it++;
        }
        break;
      case '-':
        if (it != buf.begin()) {
          it = ++buf.erase(--it);
        }
        break;
      default:
        it = ++buf.insert(it, key);
        break;
    }
  }
  for (auto c : buf) {
    cout << c;
  }
  cout << '\n';
}

int main() {
  int T;
  scanf("%d", &T);
  
  while (T--) {
    solve();
  }

  return 0;
}
