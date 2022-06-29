#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;
using LL = long long;

template<typename T>
class SegTree {
 public:
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

  size_t kth(int k) {
    return kth(k, 1, 0, n_ - 1);
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

  size_t kth(size_t k,
          size_t node_idx,
          size_t node_left,
          size_t node_right) {
    if (node_left == node_right || k == 0) {
      return node_right;
    }
    T leftSum = tree_[node_idx * 2];
    size_t mid = (node_left + node_right) / 2;
    if (leftSum >= k) {
      return kth(k, node_idx * 2, node_left, mid);
    }
    else {
      return kth(k - leftSum, node_idx * 2 + 1, mid+1, node_right);
    }
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
    return v;
  }

  static T aggregate(const T& lhs, const T& rhs) { return lhs + rhs; }

  static T falseValue() { return 0; }
};




int main() {
  int N, K;
  scanf("%d %d", &N, &K);

  vector<int> arr(N+1, 1);
  arr[0] = 0;
  SegTree<int> segTree(arr);

  vector<int> res;
  res.reserve(N);
  int i = K-1;
  for (int rem = N-1; rem >= 0; --rem) {
    int v = segTree.kth(i+1);
    res.push_back(v);
    segTree.update(v, 0);
    i += K-1;
    if (rem == 0) {
      i = 0;
    }
    else {
      i %= rem;
    }
    //printf("%d %d %d\n", i, v, rem);
  }
  
  printf("<");
  for (int i = 0; i < res.size(); ++i) {
    if (i != res.size()-1) {
      printf("%d, ", res[i]);
    }
    else {
      printf("%d>", res[i]);
    }
  }
  return 0;
}
