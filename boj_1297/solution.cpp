#include <bits/stdc++.h>
using namespace std;

int main() {
  double D, H, W;
  scanf("%lf %lf %lf", &D, &H, &W);

  double d = sqrt(H * H + W * W);
  int h = (int)(H * D / d);
  int w = (int)(W * D / d);

  printf("%d %d\n", h, w);

  return 0;
}
