#include <bits/stdc++.h>
using namespace std;

class FenwickTree {
 public:
  using T = long long;
  vector<T> arr_;
  vector<T> tree_;

 public:
  FenwickTree(size_t n) 
    : arr_(n, defaultValue()) 
    , tree_(n, defaultValue()) 
  {}

  FenwickTree(const vector<T>& arr) {
    init(arr);
  }

 public:
  void update(int i, const T& val) {
    //T diff = val - arr_[i];
    arr_[i] += val;
    while (i < tree_.size()) {
      tree_[i] += val;
      i += LSB(i);
    }
  }

  T query(int i) {
    T res = defaultValue();
    while (i > 0) {
      res += tree_[i];
      i -= LSB(i);
    }
    return res;
  }

  T query(int i, int j) {
    T res = defaultValue();
    for (i--; j > i; j -= LSB(j)) {
      res += tree_[j];
    }
    for (; i > j; i -= LSB(i)) {
      res -= tree_[i];
    }
    return res;
  }

  static inline T defaultValue() {
    return 0;
  }

  static inline int LSB(int i) { return i & (-i); }

 private:
  void init(const vector<T>& arr) {
    arr_ = arr;
    tree_ = arr;
    for (int i = 1; i < tree_.size(); ++i) {
      int j = i + LSB(i);
      if (j < tree_.size())
        tree_[j] += tree_[i];
    }
  }
};

void solve() {
  int N;
  scanf("%d", &N);

  FenwickTree fw(1000001);

  auto push = [&]() {
    int b, c;
    scanf("%d %d", &b, &c);
    fw.update(b, c);
  };

  auto pop = [&]() {
    int x;
    scanf("%d", &x);
    
    int l = 0, r = 1000000;
    while (l + 1 < r) {
      int m = (l + r) / 2;
      if (fw.query(m) < x) {
        l = m;
      }
      else {
        r = m;
      }
    }
    printf("%d\n", r);
    fw.update(r, -1);
  };

  for (int i = 0; i < N; ++i) {
    int c;
    scanf("%d", &c);
    if (c == 1) pop();
    else  push();
  }
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
