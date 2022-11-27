#include <bits/stdc++.h>
using namespace std;


vector<vector<int>> buildTree(const vector<int>& invTree) {
  vector<vector<int>> res(invTree.size());
  for (size_t i = 0; i < invTree.size(); ++i) {
    int parent = invTree[i];
    if (parent >= 0) {
      res[parent].push_back(i);
    }
  }
  return res;
}

int eulerTraversal(const vector<vector<int>>& tree,
                   int root,
                   vector<pair<int, int>>& ranges) {
  vector<int> tmp;
  ranges.resize(tree.size());
  const function<void(int)> dfs = [&](int i) -> void {
    int l = tmp.size();
    tmp.push_back(i);
    for (int j : tree[i]) {
      dfs(j);
    }
    int r = tmp.size();
    tmp.push_back(i);
    ranges[i] = {l, r};
  };
  dfs(root);
  return tmp.size();
}

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

  virtual ~SegTree(){};

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

  virtual node_t aggregate(const node_t& lhs,
                               const node_t& rhs) const = 0;
};

class RangeQuery : public SegTree<int> {
 public:
  RangeQuery(const vector<int>& data) : SegTree(data) { init(data); }

  int defaultValue() const { return 0; }

  int transform(const int& i) const { return i; }

  int aggregate(const int& l, const int& r) const { return l + r; }
};

void solve() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int N, M;
  cin >> N >> M;

  vector<int> parent(N);
  for (int i = 0; i < N; ++i) {
    cin >> parent[i];
    if (i > 0) {
      parent[i]--;
    }
  }
  auto tree = buildTree(parent);
  vector<pair<int, int>> ranges;
  int l = eulerTraversal(tree, 0, ranges);

  vector<int> data(l, 0);
  RangeQuery rsq(data);

  while (M--) {
    int queryType;
    cin >> queryType;
    switch (queryType) {
      case 1: {
        int i, w;
        cin >> i >> w;
        i--;
        auto [l, r] = ranges[i];
        rsq.update(l, rsq.query(l, l) + w);
      } break;
      case 2: {
        int i;
        cin >> i;
        i--;
        auto [l, r] = ranges[i];
        cout << rsq.query(l, r) << "\n";
      } break;
      default:
        throw runtime_error("???");
    }
  }
}

int main() {
  solve();

  return 0;
}
