#include <bits/stdc++.h>
using namespace std;

void render(vector<string>& canvas, int i, int j, int N) {
  // printf("%d %d %d\n", i, j, N);
  if (N == 0) {
    canvas[i][j] = '*';
    canvas[i + 1][j - 1] = '*';
    canvas[i + 1][j + 1] = '*';
    canvas[i + 2][j - 2] = '*';
    canvas[i + 2][j - 1] = '*';
    canvas[i + 2][j - 0] = '*';
    canvas[i + 2][j + 1] = '*';
    canvas[i + 2][j + 2] = '*';
    return;
  }
  render(canvas, i, j, N / 2);
  render(canvas, i + 3 * N, j + 3 * N, N / 2);
  render(canvas, i + 3 * N, j - 3 * N, N / 2);
}

int main() {
  int N;
  scanf("%d", &N);

  vector<string> canvas(N, string(N * 2 - 1, ' '));
  render(canvas, 0, N - 1, N / 6);

  for (string& line : canvas) {
    cout << line << "\n";
  }

  return 0;
}
