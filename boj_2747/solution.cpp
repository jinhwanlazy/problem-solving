#include <bits/stdc++.h>
using namespace std;

constexpr void initFib(array<int, 46>& arr) {
  arr[0] = 0;
  arr[1] = 1;
  for (int i = 2; i <= 45; ++i) {
    arr[i] = arr[i-1] + arr[i-2];
  }
}

int main() {
  // static table generation
  static array<int, 46> FIB;
  initFib(FIB);

  int N;
  scanf("%d", &N);
  printf("%d\n", FIB[N]);

  return 0;
}
