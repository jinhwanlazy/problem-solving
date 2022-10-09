#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  scanf("%d", &T);

  stringstream ss;
  
  while (T--) {
    int a, b;
    scanf("%d %d", &a, &b);

    ss << a + b << "\n";
  }
  cout << ss.str();

  return 0;
}
