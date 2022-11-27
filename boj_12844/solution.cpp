#include <bits/stdc++.h>
using namespace std;

template <typename T, typename node_t = T, typename lazy_t = T>
class LazySegTree {
  const node_t defaultValue_;
  const lazy_t identityValue_;

 protected:
  virtual node_t transform(const T& v) const = 0;

  virtual node_t aggregate(const node_t& lhs, const node_t& rhs) const = 0;

  virtual node_t applyLazy(const node_t& node, const lazy_t& diff) const = 0;

  virtual lazy_t compose(const lazy_t& lhs, const lazy_t& rhs) const = 0;

 public:
  size_t n_;
  size_t lg_;
  size_t width_;
  vector<node_t> tree_;
  vector<lazy_t> lazy_;

  LazySegTree(size_t n, const node_t& defaultValue, const lazy_t& identityValue)
      : defaultValue_(defaultValue),
        identityValue_(identityValue),
        n_(n),
        lg_(bit_width(n - 1)),
        width_(1 << lg_),
        tree_(width_ * 2, defaultValue),
        lazy_(width_, identityValue) {}

  virtual ~LazySegTree() {}

  void set(size_t i, const T& val) { tree_[i | width_] = transform(val); }

  void init() {
    for (size_t i = width_ - 1; i; --i)
      tree_[i] = aggregate(tree_[i << 1], tree_[i << 1 | 1]);
  }

  void update(size_t i, const lazy_t& f) {
    i |= width_;
    for (size_t j = lg_; j; j--)
      push(i >> j);
    apply(i, f);
    for (size_t j = 1; j <= lg_; j++)
      pull(i >> j);
  }

  void update(size_t l, size_t r, const lazy_t& f) {
    l |= width_, r |= width_;
    for (size_t i = lg_; i; --i) {
      if (l >> i << i != l)
        push(l >> i);
      if ((r + 1) >> i << i != r + 1)
        push(r >> i);
    }
    for (size_t L = l, R = r; L <= R; L >>= 1, R >>= 1) {
      if (L & 1)
        apply(L++, f);
      if (~R & 1)
        apply(R--, f);
    }
    for (size_t i = 1; i <= lg_; i++) {
      if (l >> i << i != l)
        pull(l >> i);
      if ((r + 1) >> i << i != r + 1)
        pull(r >> i);
    }
  }

  node_t query(size_t i) {
    i |= width_;
    for (int j = lg_; j; --j)
      push(i >> j);
    return tree_[i];
  }

  node_t query(size_t l, size_t r) {
    node_t L = defaultValue_, R = defaultValue_;
    l |= width_, r |= width_;
    for (size_t i = lg_; i; i--) {
      if (l >> i << i != l)
        push(l >> i);
      if ((r + 1) >> i << i != r + 1)
        push(r >> i);
    }
    for (; l <= r; l >>= 1, r >>= 1) {
      if (l & 1)
        L = aggregate(L, tree_[l++]);
      if (~r & 1)
        R = aggregate(tree_[r--], R);
    }
    return aggregate(L, R);
  }

 private:
  void apply(size_t i, const lazy_t& f) {
    tree_[i] = applyLazy(tree_[i], f);
    if (i < width_)
      lazy_[i] = compose(f, lazy_[i]);
  }

  void push(size_t i) {
    apply(i << 1, lazy_[i]);
    apply(i << 1 | 1, lazy_[i]);
    lazy_[i] = identityValue_;
  }

  void pull(size_t i) {
    tree_[i] = aggregate(tree_[i << 1], tree_[i << 1 | 1]);
  }
};

struct Node {
  int val;
  size_t size;
};

class RangeXorQuery : public LazySegTree<int, Node, int> {
  using LazySegTree<int, Node, int>::LazySegTree;

  Node transform(const int& i) const { return {i, 1}; }

  Node aggregate(const Node& l, const Node& r) const {
    return {l.val ^ r.val, l.size + r.size};
  }

  Node applyLazy(const Node& node, const int& K) const {
    if (node.size % 2 == 0) {
      return node;
    }
    return {node.val ^ K, node.size};
  }

  int compose(const int& lhs, const int& rhs) const { return lhs ^ rhs; }
};

void solve() {
  int N;
  scanf("%d", &N);

  RangeXorQuery rxq(N, {0, 0}, 0);
  for (int i = 0; i < N; ++i) {
    int v;
    scanf("%d", &v);
    rxq.set(i, v);
  }
  rxq.init();

  int M;
  scanf("%d", &M);

  for (int i = 0; i < M; ++i) {
    int q;
    scanf("%d", &q);
    int l, r;
    scanf("%d %d", &l, &r);
    
    if (q == 1) {
      int k;
      scanf("%d", &k);
      rxq.update(l, r, k);
    }
    else {
      printf("%d\n", rxq.query(l, r).val);
    }
  }
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
