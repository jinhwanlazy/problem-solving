#include <bits/stdc++.h>
using namespace std;

char render(int x, int y) {
  bool top_left = (x < 2) & (y < 2);
  bool vertical_line = x % 2 == 0;
  bool horizontal_line = y % 2 == 0;

  if (top_left) {
    return '.';
  }
  if (horizontal_line && vertical_line) {
    return '+';
  }
  if (horizontal_line) {
    return '-';
  }
  if (vertical_line) {
    return '|';
  }
  return '.';
}

int solution() {
  int R, C;
  cin >> R >> C;
  for (int i = 0; i < R * 2 + 1; ++i) {
    for (int j = 0; j < C * 2 + 1; ++j) {
      cout << render(j, i);
    }
    cout << "\n";
  }
  return 0;
}

int main() {
  int T;
  cin >> T;
  for (int i = 1; i <= T; ++i) {
    cout << "Case #" << i << ":\n";
    solution();
  }
  return 0;
}
