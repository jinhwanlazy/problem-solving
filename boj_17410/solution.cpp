#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;

template <typename T, typename internal_t=T>
class SegTree {
 public:
  vector<internal_t> tree_;
  size_t n_;

 public:
  SegTree(const size_t size)
      : SegTree(vector<T>(size, defaultValue())) {}

  SegTree(const vector<T>& data) {
    n_ = data.size();
    tree_.resize(4 * n_);
    std::fill(tree_.begin(), tree_.end(), defaultValue());
    init(data, 0, n_ - 1, 1);
  }

  virtual ~SegTree() {}

  int query(size_t left, size_t right, int k) {
    return query(left, right, 1, 0, n_ - 1, k);
  }

  internal_t update(size_t idx, const T& new_value) {
    return update(idx, new_value, 1, 0, n_ - 1);
  }

 private:
  internal_t init(const vector<T>& data, size_t left, size_t right, size_t node_idx) {
    if (left == right) {
      return tree_[node_idx] = transform(data[left]);
    }
    size_t mid = (left + right) / 2;
    internal_t res_left = init(data, left, mid, node_idx * 2);
    internal_t res_right = init(data, mid + 1, right, node_idx * 2 + 1);
    return tree_[node_idx] = aggregate(res_left, res_right);
  }

  int query(size_t left,
          size_t right,
          size_t node_idx,
          size_t node_left,
          size_t node_right, 
          int k) {
    if (right < node_left || node_right < left) {
      return 0;
    }
    if (left <= node_left && node_right <= right) {
      auto& xs = tree_[node_idx];
      auto res = xs.end() - upper_bound(xs.begin(), xs.end(), k);
      return res;
    }
    size_t mid = (node_left + node_right) / 2;
    auto res_left = query(left, right, node_idx * 2, node_left, mid, k);
    auto res_right = query(left, right, node_idx * 2 + 1, mid + 1, node_right, k);
    return res_left + res_right;
  }

  template <typename U>
  internal_t update(size_t idx,
           const U& new_value,
           size_t node_idx,
           size_t node_left,
           size_t node_right) {
    if (idx < node_left || node_right < idx) {
      return tree_[node_idx];
    }
    if (node_left == node_right) {
      return tree_[node_idx] = transform(new_value);
    }
    size_t mid = (node_left + node_right) / 2;
    internal_t res_left = update(idx, new_value, node_idx * 2, node_left, mid);
    internal_t res_right = update(idx, new_value, node_idx * 2 + 1, mid + 1, node_right);
    return tree_[node_idx] = aggregate(res_left, res_right);
  }

public:
  template <typename V>
  static vector<V> merge(const vector<V>& lhs, const vector<V>& rhs) {
    auto lIt = lhs.begin();
    auto rIt = rhs.begin();
    vector<V> res;
    res.reserve(lhs.size() + rhs.size());
    while (lIt != lhs.end() || rIt != rhs.end()) {
      auto* it = &lIt;
      if (lIt == lhs.end())
        it = &rIt;
      else if (rIt == rhs.end())
        it = &lIt;
      else
        it = (*lIt <= *rIt) ? &lIt : &rIt;

      res.push_back(**it);
      (*it)++;
    }
    return res;
  }
  
  virtual inline internal_t defaultValue() = 0;

  virtual inline internal_t transform(const T& v) = 0;

  virtual inline internal_t aggregate(const internal_t& lhs, const internal_t& rhs) = 0;
};


void solve() {
  int N;
  scanf("%d", &N);

  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &A[i]);
  }
  
  SegTree<SegTree<int>> tree(A);
  
  int K;
  scanf("%d", &K);
  while (K--) {
    int Q;
    scanf("%d", &Q);
    if (Q == 1) {
      int i, v;
      scanf("%d %d", &i, &v);
      tree.update(i-1, v);
    } else {
      int i, j, k;
      scanf("%d %d %d", &i, &j, &k);
      int ans = tree.query(i-1, j-1, k);
      printf("%d\n", ans);
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
