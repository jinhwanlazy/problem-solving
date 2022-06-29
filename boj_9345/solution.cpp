#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;
using LL = long long;
constexpr static int INF = numeric_limits<int>::max();

template<typename T>
class SegTree {
 private:
  vector<T> tree_;
  size_t n_;

 public:
  template <typename U>
  SegTree(const size_t size, const U& default_value)
      : SegTree(vector<U>(size, default_value)) {}

  template <typename U>
  SegTree(const vector<U>& data) {
    n_ = data.size();
    tree_.resize(4 * n_);
    std::fill(tree_.begin(), tree_.end(), falseValue());
    init(data, 0, n_ - 1, 1);
  }

  T query(size_t left, size_t right) {
    return query(left, right, 1, 0, n_ - 1);
  }

  template <typename U>
  T update(size_t idx, const U& new_value) {
    return update(idx, new_value, 1, 0, n_ - 1);
  }

 private:
  template <typename U>
  T init(const vector<U>& data, size_t left, size_t right, size_t node_idx) {
    if (left == right) {
      return tree_[node_idx] = transform(data[left]);
    }
    size_t mid = (left + right) / 2;
    T res_left = init(data, left, mid, node_idx * 2);
    T res_right = init(data, mid + 1, right, node_idx * 2 + 1);
    return tree_[node_idx] = aggregate(res_left, res_right);
  }

  T query(size_t left,
          size_t right,
          size_t node_idx,
          size_t node_left,
          size_t node_right) {
    if (right < node_left || node_right < left) {
      return falseValue();
    }
    if (left <= node_left && node_right <= right) {
      return tree_[node_idx];
    }
    size_t mid = (node_left + node_right) / 2;
    T res_left = query(left, right, node_idx * 2, node_left, mid);
    T res_right = query(left, right, node_idx * 2 + 1, mid + 1, node_right);
    return aggregate(res_left, res_right);
  }

  template <typename U>
  T update(size_t idx,
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
    T res_left = update(idx, new_value, node_idx * 2, node_left, mid);
    T res_right = update(idx, new_value, node_idx * 2 + 1, mid + 1, node_right);
    return tree_[node_idx] = aggregate(res_left, res_right);
  }

  template <typename U>
  static T transform(const U& v) {
    return {v, v};
  }

  static T aggregate(const T& lhs, const T& rhs) {
    return {min(lhs.first, rhs.first), max(lhs.second, rhs.second)};
  }

  static T falseValue() { return {INF, -INF}; }
};

int main() {
  int T;
  scanf("%d", &T);

  while (T--) {
    int N, K;
    scanf("%d %d", &N, &K);
    
    vector<LL> xs(N); 
    iota(all(xs), 0);
    SegTree<pair<LL, LL>> tree(xs);

    for (int i = 0; i < K; ++i) {
      int q, a, b;
      scanf("%d %d %d", &q, &a, &b);
      if (q == 0) {
        auto& aVal = xs[a];
        auto& bVal = xs[b];
        tree.update(a, bVal);
        tree.update(b, aVal);
        swap(aVal, bVal);
      }
      else {
        auto minmax = tree.query(a, b);
        if (minmax.first == a && minmax.second == b) {
          printf("YES\n");
        }
        else {
          printf("NO\n");
        }
      }
    }
  }

  return 0;
}
