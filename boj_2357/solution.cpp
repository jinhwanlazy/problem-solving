#include <bits/stdc++.h>
using namespace std;

using LL = long long;

template <typename T, typename internal_t = T>
class SegTree {
 public:
  const function<internal_t()> defaultFn_;
  const function<internal_t(const T&)> transformFn_;
  const function<internal_t(const internal_t&, const internal_t&)> aggregateFn_;
  size_t n_;
  vector<internal_t> tree_;

  SegTree(const vector<T>& data,
          const function<internal_t()>&& defaultFn,
          const function<internal_t(const T&)>&& transformFn,
          const function<internal_t(const internal_t&, const internal_t&)>&& aggregateFn)
      : defaultFn_(defaultFn),
        transformFn_(transformFn),
        aggregateFn_(aggregateFn),
        n_(data.size()),
        tree_(4 * n_, defaultFn_()) {
    init(data, 0, n_ - 1, 1);
  }

  internal_t query(size_t left, size_t right) {
    return query(left, right, 1, 0, n_ - 1);
  }

  internal_t update(size_t idx, const T& newValue) {
    return update(idx, newValue, 1, 0, n_ - 1);
  }

 private:
  internal_t init(const vector<T>& data,
                  size_t left,
                  size_t right,
                  size_t nodeIdx) {
    if (left == right) {
      return tree_[nodeIdx] = transformFn_(data[left]);
    }
    size_t mid = (left + right) / 2;
    internal_t res_left = init(data, left, mid, nodeIdx * 2);
    internal_t res_right = init(data, mid + 1, right, nodeIdx * 2 + 1);
    return tree_[nodeIdx] = aggregateFn_(res_left, res_right);
  }

  internal_t query(size_t left,
                   size_t right,
                   size_t nodeIdx,
                   size_t nodeLeft,
                   size_t nodeRight) {
    if (right < nodeLeft || nodeRight < left) {
      return defaultFn_();
    }
    if (left <= nodeLeft && nodeRight <= right) {
      return tree_[nodeIdx];
    }
    size_t mid = (nodeLeft + nodeRight) / 2;
    internal_t res_left = query(left, right, nodeIdx * 2, nodeLeft, mid);
    internal_t res_right =
        query(left, right, nodeIdx * 2 + 1, mid + 1, nodeRight);
    return aggregateFn_(res_left, res_right);
  }

  internal_t update(size_t idx,
                    const T& value,
                    size_t nodeIdx,
                    size_t nodeLeft,
                    size_t nodeRight) {
    if (idx < nodeLeft || nodeRight < idx) {
      return tree_[nodeIdx];
    }
    if (nodeLeft == nodeRight) {
      return tree_[nodeIdx] = transformFn_(value);
    }
    size_t mid = (nodeLeft + nodeRight) / 2;
    internal_t res_left = update(idx, value, nodeIdx * 2, nodeLeft, mid);
    internal_t res_right =
        update(idx, value, nodeIdx * 2 + 1, mid + 1, nodeRight);
    return tree_[nodeIdx] = aggregateFn_(res_left, res_right);
  }
};


int main() {
  int N, M;
  scanf("%d %d", &N, &M);

  vector<LL> arr(N);
  for (int i = 0; i < N; ++i) {
    scanf("%lld", &arr[i]);
  }

  SegTree<LL, pair<LL, LL>> tree(
      arr,
      []() -> pair<LL, LL> {
        return {1000000000, 0};
      },
      [](const LL& v) -> pair<LL, LL> {
        return {v, v};
      },
      [](const pair<LL, LL>& lhs, const pair<LL, LL>& rhs) -> pair<LL, LL> {
        return {min(lhs.first, rhs.first), max(lhs.second, rhs.second)};
      });

  for (int i = 0; i < M; ++i) {
    LL a, b;
    scanf("%lld %lld", &a, &b);
    auto res = tree.query(a-1, b-1);
    cout << res.first << " " << res.second << "\n";
  }

  return 0;
}
