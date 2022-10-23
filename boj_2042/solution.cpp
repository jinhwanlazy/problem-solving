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

class RangeSumQuery : public SegTree<LL> {
  using SegTree<LL>::SegTree;

  LL transform(const LL& i) const { return i; }

  LL aggregate(const LL& l, const LL& r) const { return l + r; }
};

template <typename T>
class FenwickTree {
  const T defaultValue_;

 public:
  vector<T> arr_;
  vector<T> tree_;

  FenwickTree(int n, const T& defaultValue)
      : defaultValue_(defaultValue),
        arr_(n, defaultValue_),
        tree_(n, defaultValue_) {}

  void set(int i, const T& val) { arr_[i] = val; }

  void init() {
    tree_ = arr_;
    for (int i = 1, iEnd=(int)tree_.size(); i < iEnd; ++i) {
      int j = i + LSB(i);
      if (j < (int)tree_.size())
        tree_[j] += tree_[i];
    }
  }

  void update(int i, const T& val) {
    T diff = val - arr_[i];
    arr_[i] = val;
    while (i < tree_.size()) {
      tree_[i] += diff;
      i += LSB(i);
    }
  }

  T query(int i) {
    T res = defaultValue_;
    while (i > 0) {
      res += tree_[i];
      i -= LSB(i);
    }
    return res;
  }

  T query(int i, int j) {
    T res = defaultValue_;
    for (i--; j > i; j -= LSB(j))
      res += tree_[j];
    for (; i > j; i -= LSB(i))
      res -= tree_[i];
    return res;
  }

 private:
  static inline int LSB(int i) { return i & (-i); }
};

int main() {
  int N, M, K;
  scanf("%d %d %d", &N, &M, &K);

  //RangeSumQuery rsq(N, 0);
  //for (int i = 0; i < N; ++i) {
    //LL v;
    //scanf("%lld", &v);
    //rsq.set(i, v);
  //}
  //rsq.init();
  
  //for (int i = 0; i < M + K; ++i) {
    //LL a, b, c;
    //scanf("%lld %lld %lld", &a, &b, &c);
    //if (a == 1) {  // update
      //rsq.update(b - 1, c);
    //}
    //if (a == 2) {  // query
      //cout << rsq.query(b - 1, c - 1) << "\n";
    //}
  //}

  FenwickTree<LL> tree(N+1, 0);
  for (int i = 1; i <= N; ++i) {
    LL v;
    scanf("%lld", &v);
    tree.set(i, v);
  }
  tree.init();

  for (int i = 0; i < M + K; ++i) {
    LL a, b, c;
    scanf("%lld %lld %lld", &a, &b, &c);
    if (a == 1) {
      tree.update(b, c);
    }
    else  {
      LL ans = tree.query(b, c);
      printf("%lld\n", ans);
    }
  }
  return 0;
}
