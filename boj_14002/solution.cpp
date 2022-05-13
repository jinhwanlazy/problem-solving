#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;
  scanf("%d", &N);

  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &A[i]);
  }

  vector<int> LIS{numeric_limits<int>::min()};
  vector<int> trace(N);

  for (int i = 0; i < N; ++i) {
    int a = A[i];
    if (LIS.back() < a) {
      trace[i] = LIS.size();
      LIS.push_back(a);
    } else {
      auto j = lower_bound(LIS.begin(), LIS.end(), a) - LIS.begin();
      trace[i] = j;
      LIS[j] = a;
    }
  }

  printf("%ld\n", LIS.size() - 1);
  int t = LIS.size() - 1;
  vector<int> ans;
  for (int i = trace.size() - 1; i >= 0; --i) {
    if (trace[i] == t) {
      ans.push_back(A[i]);
      t--;
    }
  }
  sort(ans.begin(), ans.end());
  for (int i = 0; i < ans.size(); ++i) {
    printf("%d ", ans[i]);
  }
  printf("\n");

  return 0;
}
