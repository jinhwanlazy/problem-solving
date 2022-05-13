#include <bits/stdc++.h>
using namespace std;

int sq(int i) {
  return i * i;
}

int main() {
  int sticks[3];
  scanf("%d %d %d", sticks, sticks + 1, sticks + 2);

  sort(sticks, sticks + 3);

  if (sq(sticks[2]) == sq(sticks[0]) + sq(sticks[1])) {
    printf("1\n");
  } else if (sticks[0] == sticks[1] && sticks[1] == sticks[2]) {
    printf("2\n");
  } else {
    printf("0\n");
  }

  return 0;
}
