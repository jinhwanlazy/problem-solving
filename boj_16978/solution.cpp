#include <bits/stdc++.h>
using namespace std;

using LL = long long;

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

  void set(size_t i, const T& val) { tree_[i | width_] = transform(val); }

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

class RangeSumQuery : public SegTree<LL> {
  using SegTree<LL>::SegTree;

  LL transform(const LL& i) const { return i; }

  LL aggregate(const LL& l, const LL& r) const { return l + r; }
};

struct Q1 {
  int i;
  int v;
};

struct Q2 {
  int t;
  int k;
  int l;
  int r;
  LL result;
};

void solve() {
  int N;
  scanf("%d", &N);

  RangeSumQuery rsq(N + 1, 0);
  for (int i = 1; i <= N; ++i) {
    LL x;
    scanf("%lld", &x);
    rsq.set(i, x);
  }
  rsq.init();

  int M;
  scanf("%d", &M);

  vector<Q1> q1s;
  vector<Q2> q2s;
  for (int t = 0; t < M; ++t) {
    int queryType;
    scanf("%d", &queryType);
    if (queryType == 1) {
      int i, v;
      scanf("%d %d", &i, &v);
      q1s.push_back({i, v});
    } else if (queryType == 2) {
      int k, l, r;
      scanf("%d %d %d", &k, &l, &r);
      q2s.push_back({t, k, l, r, (LL)-1});
    }
  }

  sort(q2s.begin(), q2s.end(),
       [](const auto& q1, const auto& q2) -> bool { return q1.k < q2.k; });
  int k = 0;
  for (auto& q2 : q2s) {
    while (k < q2.k) {
      const auto& q1 = q1s[k];
      rsq.update(q1.i, q1.v);
      k++;
    }
    q2.result = rsq.query(q2.l, q2.r);
  }

  sort(q2s.begin(), q2s.end(),
       [](const auto& q1, const auto& q2) -> bool { return q1.t < q2.t; });

  for (auto& q2 : q2s) {
    printf("%lld\n", q2.result);
  }
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
