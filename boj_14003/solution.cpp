#include <bits/stdc++.h>
using namespace std;

int main() {
  vector<int> v;
  v.push_back(numeric_limits<int>::min());

  int N;
  scanf("%d", &N);

  while (N--) {
    int i;
    scanf("%d", &i);
    if (v.back() < i) {
      v.push_back(i);
    } else {
      auto it = lower_bound(v.begin(), v.end(), i);
      *it = i;
    }
  }
  printf("%ld\n", v.size() - 1);
  for (int i = 1; i < v.size(); ++i) {
    printf("%d ", v[i]);
  }
  return 0;
}
