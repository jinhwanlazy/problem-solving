#include <bits/stdc++.h>
using namespace std;

class LIS {
  using T = int;
 public:
  vector<T> arr;
  vector<T> trace;
  size_t length;
  
  LIS(const vector<T>& arr) : arr(arr), trace(0), length(0) {}

  size_t solve() {
    vector<T> tmp = {numeric_limits<int>::min()};
    trace.resize(arr.size(), 0);

    for (size_t i = 0; i < arr.size(); ++i) {
      int a = arr[i];
      if (tmp.back() < a) {
        trace[i] = tmp.size();
        tmp.push_back(a);
      } else {
        auto j = lower_bound(tmp.begin(), tmp.end(), a) - tmp.begin();
        trace[i] = j;
        tmp[j] = a;
      }
    }
    length = tmp.size() - 1;
    return length;
  }

  vector<int> indices() const {
    int t = length;
    vector<int> res;
    for (int i = trace.size() - 1; i >= 0; --i) {
      if (trace[i] == t) {
        res.push_back(i);
        t--;
      }
    }
    
    reverse(res.begin(), res.end());
    return res;
  }
};

void solve() {
  int N;
  scanf("%d", &N);

  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &A[i]);
  }

  LIS lis(A);
  printf("%lu\n", lis.solve());
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
