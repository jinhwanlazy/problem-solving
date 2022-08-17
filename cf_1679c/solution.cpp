#include <bits/stdc++.h>
using namespace std;

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
    return v;
  }

  static T aggregate(const T& lhs, const T& rhs) { return lhs + rhs; }

  static T falseValue() { return 0; }
};

int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);

  SegTree<int> x_occupancy(N+1, 0);
  SegTree<int> y_occupancy(N+1, 0);
  vector<int> x_count(N+1, 0);
  vector<int> y_count(N+1, 0);

  for (int i = 0; i < Q; ++i) {
    int query;
    cin >> query;
    switch (query) {
      case 1: {
        int x, y;
        scanf("%d %d", &x, &y);
        x_count[x]++;
        y_count[y]++;
        x_occupancy.update(x, 1);
        y_occupancy.update(y, 1);
      } break;
      case 2: {
        int x, y;
        scanf("%d %d", &x, &y);
        x_count[x]--;
        y_count[y]--;
        if (x_count[x] == 0) {
          x_occupancy.update(x, 0);
        }
        if (y_count[y] == 0) {
          y_occupancy.update(y, 0);
        }
      } break;
      case 3: {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        bool x_covered = x_occupancy.query(x1, x2) == x2 - x1 + 1;
        bool y_covered = y_occupancy.query(y1, y2) == y2 - y1 + 1;
        if (x_covered || y_covered) {
          cout << "Yes\n";
        }
        else {
          cout << "No\n";
        }
      } break;
      default:
        break;
    }
  }

  return 0;
}
