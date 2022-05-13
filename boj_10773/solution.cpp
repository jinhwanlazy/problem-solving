#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  cin >> N;

  vector<int> s;
  for (int i = 0; i < N; ++i) {
    int x;
    cin >> x;
    if (x == 0) {
      s.pop_back();
    } else {
      s.push_back(x);
    }
  }
  cout << accumulate(s.begin(), s.end(), 0) << "\n";
  return 0;
}
