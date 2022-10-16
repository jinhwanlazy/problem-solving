#include <bits/stdc++.h>
using namespace std;

using LL = long long;

template <typename T, typename node_t = T>
class SegTree {
 public:
  size_t n_;
  vector<node_t> tree_;

  node_t query(size_t left, size_t right) {
    return query(left, right, 1, 0, n_ - 1);
  }

  node_t update(size_t idx, const T& newValue) {
    return update(idx, newValue, 1, 0, n_ - 1);
  }

  virtual ~SegTree() {};

 protected:
  SegTree(const vector<T>& data) : n_(data.size()), tree_(4 * n_) {}
  
  void init(const vector<T>& data) { init(data, 0, n_ - 1, 1); }

  node_t init(const vector<T>& data,
                  size_t left,
                  size_t right,
                  size_t nodeIdx) {
    if (left == right) {
      return tree_[nodeIdx] = transform(data[left]);
    }
    size_t mid = (left + right) / 2;
    node_t res_left = init(data, left, mid, nodeIdx * 2);
    node_t res_right = init(data, mid + 1, right, nodeIdx * 2 + 1);
    return tree_[nodeIdx] = aggregate(res_left, res_right);
  }

  node_t query(size_t left,
                    size_t right,
                    size_t nodeIdx,
                    size_t nodeLeft,
                    size_t nodeRight) {
    if (right < nodeLeft || nodeRight < left) {
      return defaultValue();
    }
    if (left <= nodeLeft && nodeRight <= right) {
      return tree_[nodeIdx];
    }
    size_t mid = (nodeLeft + nodeRight) / 2;
    node_t res_left = query(left, right, nodeIdx * 2, nodeLeft, mid);
    node_t res_right =
        query(left, right, nodeIdx * 2 + 1, mid + 1, nodeRight);
    return aggregate(res_left, res_right);
  }

  node_t update(size_t idx,
                    const T& value,
                    size_t nodeIdx,
                    size_t nodeLeft,
                    size_t nodeRight) {
    if (idx < nodeLeft || nodeRight < idx) {
      return tree_[nodeIdx];
    }
    if (nodeLeft == nodeRight) {
      return tree_[nodeIdx] = transform(value);
    }
    size_t mid = (nodeLeft + nodeRight) / 2;
    node_t res_left = update(idx, value, nodeIdx * 2, nodeLeft, mid);
    node_t res_right =
        update(idx, value, nodeIdx * 2 + 1, mid + 1, nodeRight);
    return tree_[nodeIdx] = aggregate(res_left, res_right);
  }

  virtual node_t defaultValue() const = 0;

  virtual node_t transform(const T& v) const = 0;

  virtual node_t aggregate(const node_t& lhs, const node_t& rhs) const = 0;
};

class RangeQuery : public SegTree<LL, pair<LL, LL>>
{
public:
  RangeQuery(const vector<LL>& data) : SegTree(data) {
    init(data);
  }
  
  pair<LL, LL> defaultValue() const { return {10000000000, 0}; }

  pair<LL, LL> transform(const LL& i) const { return {i, i}; }

  pair<LL, LL> aggregate(const pair<LL, LL>& lhs, const pair<LL, LL>& rhs) const {
        return {min(lhs.first, rhs.first), max(lhs.second, rhs.second)};
  }
};


int main() {
  int N, M;
  scanf("%d %d", &N, &M);

  vector<LL> arr(N);
  for (int i = 0; i < N; ++i) {
    scanf("%lld", &arr[i]);
  }

  RangeQuery tree(arr);

  for (int i = 0; i < M; ++i) {
    LL a, b;
    scanf("%lld %lld", &a, &b);
    auto res = tree.query(a-1, b-1);
    cout << res.first << " " << res.second << "\n";
  }

  return 0;
}
