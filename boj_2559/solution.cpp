#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, K;
  scanf("%d %d", &N, &K);

  vector<int> xs(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &xs[i]);
  }

  deque<int> window;
  int max_sum = 0;
  int sum = 0;
  for (int i = 0; i < K; ++i) {
    sum += xs[i];
    window.push_back(xs[i]);
  }
  max_sum = sum;
  for (int i = K; i < N; ++i) {
    sum += xs[i];
    window.push_back(xs[i]);
    sum -= window.front();
    window.pop_front();
    max_sum = max(max_sum, sum);
  }
  printf("%d\n", max_sum);

  return 0;
}
