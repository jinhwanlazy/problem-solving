#include <bits/stdc++.h>
using namespace std;

unsigned int expand_bits(unsigned int v) {
  v = (v | v << 8) & 0x00FF00FF;
  v = (v | v << 4) & 0x0F0F0F0F;
  v = (v | v << 2) & 0x33333333;
  v = (v | v << 1) & 0x55555555;
  return v;
}

unsigned int morton2D(unsigned int x, unsigned int y)
{
	unsigned int xx = expand_bits(x);
	unsigned int yy = expand_bits(y);
	return xx | (yy << 1);
}

int main() {
  int N, r, c;
  scanf("%d %d %d", &N, &r, &c);

  unsigned ans = morton2D(c, r);
  printf("%u\n", ans);

  return 0;
}

