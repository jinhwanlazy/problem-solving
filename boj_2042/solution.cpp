#include <bits/stdc++.h>
using namespace std;

using LL = long long;

template<typename T>
class SegTree {
  public:
  vector<T> tree_;
  size_t n_;

  template<typename U>
  SegTree(const vector<U>& data) {
    n_ = data.size();
    tree_.resize(4 * n_);
    std::fill(tree_.begin(), tree_.end(), falseValue());
    init(data, 0, n_-1, 1);
  }

  T query(size_t left, size_t right) {
    return query(left, right, 1, 0, n_-1);
  }
  
  template<typename U>
  T update(size_t idx, const U& new_value) {
    return update(idx, new_value, 1, 0, n_-1);
  }

 private:
  template<typename U>
  T init(const vector<U>& data, size_t left, size_t right, size_t node_idx) {
    if (left == right) {
      return tree_[node_idx] = transform(data[left]);
    }
    size_t mid = (left + right) / 2;
    T res_left = init(data, left, mid, node_idx * 2);
    T res_right = init(data, mid+1, right, node_idx * 2 + 1);
    return tree_[node_idx] = aggregate(res_left, res_right);
  }

  T query(size_t left, size_t right, size_t node_idx, size_t node_left, size_t node_right) {
    if (right < node_left || node_right < left) {
      return falseValue();
    }
    if (left <= node_left && node_right <= right) {
      return tree_[node_idx];
    }
    size_t mid = (node_left + node_right) / 2;
    T res_left = query(left, right, node_idx * 2, node_left, mid);
    T res_right = query(left, right, node_idx * 2 + 1, mid+1, node_right);
    return aggregate(res_left, res_right);
  }

  template<typename U>
  T update(size_t idx, const U& new_value, size_t node_idx, size_t node_left, size_t node_right) {
    if (idx < node_left || node_right < idx) {
      return tree_[node_idx];
    }
    if (node_left == node_right) {
      return tree_[node_idx] = transform(new_value);
    }
    size_t mid = (node_left + node_right) / 2;
    T res_left = update(idx, new_value, node_idx * 2, node_left, mid);
    T res_right = update(idx, new_value, node_idx * 2 + 1, mid+1, node_right);
    return tree_[node_idx] = aggregate(res_left, res_right);
  }

  template<typename U>
  static T transform(const U& v) {
    return v;
  }
  
  static T aggregate(const T& lhs, const T& rhs) {
    return lhs + rhs;
  }

  static T falseValue() {
    return 0;
  }
};

template <typename T>
class FenwickTree {
 public:
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
    T diff = val - arr_[i];
    arr_[i] = val;
    while (i < tree_.size()) {
      tree_[i] += diff;
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

int main() {
  int N, M, K;
  scanf("%d %d %d", &N, &M, &K);
  
  //vector<LL> arr(N);
  //for (int i = 0; i < N; ++i) {
    //scanf("%lld", &arr[i]);
  //}
  //SegTree<LL> tree(arr);
  //for (int i = 0; i < M+K; ++i) {
    //LL a, b, c;
    //scanf("%lld %lld %lld", &a, &b, &c);
    //if (a == 1) { // update
      //tree.update(b-1, c);
    //}
    //if (a == 2) { // query
      //cout << tree.query(b-1, c-1) << "\n";
    //}
  //}
  

  vector<LL> arr(N+1);
  for (int i = 1; i <= N; ++i) {
    scanf("%lld", &arr[i]);
  }
  FenwickTree<LL> tree(arr);

  for (int i = 0; i < M + K; ++i) {
    LL a, b, c;
    scanf("%lld %lld %lld", &a, &b, &c);
    if (a == 1) {  // update
      tree.update(b, c);
    }
    if (a == 2) {  // query
      LL ans = tree.query(b, c);
      printf("%lld\n", ans);
    }
  }
  return 0;
}
