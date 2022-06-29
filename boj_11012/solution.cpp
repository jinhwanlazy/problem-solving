#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;
using PII = pair<int, int>;

class FenwickTree {
 public:
  vector<vector<int>> tree_;

 public:
  FenwickTree(size_t n) : tree_(n) {}

 public:
  // tree stores vector of sorted y coords
  void insert(int i, int val) {
    while (i < tree_.size()) {
      tree_[i].push_back(val);
      i += LSB(i);
    }
  }

  // returns count of y coords below val. O(log(N)^2)
  int query(int i, int val) {
    int res = 0;
    while (i > 0) {
      const auto& bin = tree_[i];
      res += lower_bound(all(bin), val) - bin.begin();
      i -= LSB(i);
    }
    return res;
  }

  static inline int LSB(int i) { return i & (-i); }
};

void solution() {
  int N, M;
  scanf("%d %d", &N, &M);

  vector<PII> points(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d %d", &points[i].first, &points[i].second);
  }

  sort(all(points), [](const auto& lhs, const auto& rhs) -> bool {
    return lhs.second < rhs.second;
  });

  FenwickTree tree(100001);
  for (const auto& [x, y] : points) {
    tree.insert(x, y);
  }

  int ans = 0;
  for (int i = 0; i < M; ++i) {
    int l, r, b, t;
    scanf("%d %d %d %d", &l, &r, &b, &t);

    ans += tree.query(r, t + 1);
    ans -= tree.query(r, b);
    ans -= tree.query(l - 1, t + 1);
    ans += tree.query(l - 1, b);
  }
  printf("%d\n", ans);
}

int main() {
  int T;
  scanf("%d", &T);

  while (T--) {
    solution();
  }

  return 0;
}
