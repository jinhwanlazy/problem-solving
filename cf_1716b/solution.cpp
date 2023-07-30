#include <bits/stdc++.h>
using namespace std;

void solve() {
  int N;
  scanf("%d", &N);

  vector<int> arr(N);
  iota(arr.begin(), arr.end(), 1);

  printf("%d\n", N);

  for (int i = 0; i < arr.size(); ++i) {
    printf("%d ", arr[i]);
  }
  printf("\n");
  
  for (int i = 0; i + 1 < N; ++i) {
    int j = i + 1;
    swap(arr[i], arr[j]);
    for (int i = 0; i < arr.size(); ++i) {
      printf("%d ", arr[i]);
    }
    printf("\n");
  }

}

int main() {
  int T;
  scanf("%d", &T);
  
  while (T--) {
    solve();
  }

  return 0;
}
