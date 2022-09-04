#include <bits/stdc++.h>
using namespace std;

using LL = long long;

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

  vector<pair<int, int>> ps(N);
  map<int, int> b2a;
  for (int i = 0; i < N; ++i) {
    auto& [a, b] = ps[i];
    scanf("%d %d", &a, &b);
    b2a[b] = a;
  }

  sort(ps.begin(), ps.end());
  
  vector<int> xs;
  xs.reserve(N);
  for (int i = 0; i < N; ++i) {
    xs.push_back(ps[i].second);
  }

  LIS lis(xs);
  lis.solve();
  auto selected = lis.indices();
  set<int> selectedSet(selected.begin(), selected.end());
  printf("%lu\n", N - selected.size());

  vector<int> ans;
  for (int i = 0; i < N; ++i) {
    if (selectedSet.find(i) == selectedSet.end()) {
      ans.push_back(b2a[xs[i]]);
    }
  }
  sort(ans.begin(), ans.end());
  for (int i = 0; i < ans.size(); ++i) {
    printf("%d\n", ans[i]);
  }
  printf("\n");
  
  

}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
