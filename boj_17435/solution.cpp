#include <bits/stdc++.h>
using namespace std;

class SparseTable {
  vector<vector<int>> table_;
  int maxDepth_;

 public:
  SparseTable(const vector<int>& f, int maxDepth = 20)
      : table_(maxDepth), maxDepth_(maxDepth) {
    table_[0] = f;
    for (int i = 1; i < maxDepth; ++i) {
      const vector<int>& prev = table_[i - 1];
      vector<int>& row = table_[i];
      row.resize(prev.size());
      for (int j = 0; j < row.size(); ++j) {
        row[j] = prev[prev[j]];
      }
    }
  }

  int query(int n, int x) const {
    for (int i = 0; i < maxDepth_; ++i) {
      if ((n >> i) & 1) {
        x = table_[i][x];
      }
    }
    return x;
  }
};

int main() {
  int m;
  scanf("%d", &m);

  vector<int> f(m);
  for (int i = 0; i < m; ++i) {
    scanf("%d", &f[i]);
    f[i]--;
  }

  SparseTable table(f);

  int Q;
  scanf("%d", &Q);
  for (int i = 0; i < Q; ++i) {
    int n, x;
    scanf("%d %d", &n, &x);

    int y = table.query(n, x - 1);
    printf("%d\n", y + 1);
  }
  return 0;
}
