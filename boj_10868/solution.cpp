#include <bits/stdc++.h>
using namespace std;

template <typename T, typename node_t = T>
class SegTree {
  const node_t defaultValue_;

 protected:
  virtual node_t transform(const T& v) const = 0;

  virtual node_t aggregate(const node_t& lhs, const node_t& rhs) const = 0;

 public:
  size_t n_;
  size_t width_;
  vector<node_t> tree_;

  virtual ~SegTree(){};

  SegTree(size_t n, const node_t& defaultValue)
      : defaultValue_(defaultValue),
        n_(n),
        width_(1 << bit_width(n - 1)),
        tree_(width_ * 2, defaultValue) {}

  void set(size_t i, const T& val) {
    tree_[i | width_] = transform(val);
  }

  void init() {
    for (size_t i = width_ - 1; i; --i) 
      tree_[i] = aggregate(tree_[i << 1], tree_[i << 1 | 1]);
  }

  void update(size_t i, const T& val) {
    tree_[i |= width_] = transform(val);
    while (i >>= 1)
      tree_[i] = aggregate(tree_[i << 1], tree_[i << 1 | 1]);
  }

  node_t query(size_t i) const { return tree_[i | width_]; }

  node_t query(size_t l, size_t r) const {
    node_t L = defaultValue_;
    node_t R = defaultValue_;
    for (l |= width_, r |= width_; l <= r; l >>= 1, r >>= 1) {
      if (l & 1)
        L = aggregate(L, tree_[l++]);
      if (~r & 1)
        R = aggregate(tree_[r--], R);
    }
    return aggregate(L, R);
  }
};

class RangeMinQuery : public SegTree<int> {
  using SegTree<int>::SegTree;

  int transform(const int& i) const { return i; }

  int aggregate(const int& l, const int& r) const { return min(l, r); }
};

void solve() {
  int N, M;
  scanf("%d %d", &N, &M);

  RangeMinQuery rmq(N, std::numeric_limits<int>::max());
  for (int i = 0; i < N; ++i) {
    int x;
    scanf("%d", &x);
    rmq.set(i, x);
  }
  rmq.init();

  for (int i = 0; i < M; ++i) {
    int a, b;
    scanf("%d %d", &a, &b);
    int ans = rmq.query(--a, --b);
    printf("%d\n", ans);
  }
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
