#include <bits/stdc++.h>
using namespace std;

struct UnionFindSet {
  UnionFindSet(int size) : root_(size), rank_(size, 0), size_(size, 1) {
    for (int i = 0; i < size; ++i) {
      root_[i] = i;
    }
  }

  int find(int i) {
    if (root_[i] == i) {
      return i;
    }
    int root = find(root_[i]);
    root_[i] = root;
    return root;
  }

  int merge(int i, int j) {
    int i_root = find(i);
    int j_root = find(j);
    if (i_root == j_root) {
      return size_[i_root];
    }
    if (rank_[i_root] < rank_[j_root]) {
      root_[i_root] = j_root;
      size_[j_root] += size_[i_root];
      size_[i_root] = 0;
      return size_[j_root];
    }
    root_[j_root] = i_root;
    size_[i_root] += size_[j_root];
    size_[j_root] = 0;
    if (rank_[i_root] == rank_[j_root]) {
      rank_[i_root]++;
    }
    return size_[i_root];
  }

  bool resize(size_t size) {
    size_t size_before = root_.size();

    if (size_before >= size) {
      return false;
    }
    root_.resize(size);
    rank_.resize(size, 0);
    size_.resize(size, 1);
    for (size_t i = size_before; i < size; ++i) {
      root_[i] = i;
    }
    return true;
  }

  size_t size() const {
    return root_.size();
  }

  vector<int> root_;
  vector<int> rank_;
  vector<int> size_;
};


int knapsack(int N, int K, const vector<int>& W, const vector<int>& V) {
  /*
   * dp[i][j] := 1~i번째 물건으로 크기 j인 배낭을 채웠을 때의 최대 가치
   */
  vector<vector<int>> dp(N + 1, vector<int>(K + 1, 0));
  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= K; ++j) {
      int w = W[i - 1];
      int v = V[i - 1];
      if (w > j) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] = max(dp[i - 1][j - w] + v, dp[i - 1][j]);
      }
    }
  }
  return dp.back().back();
}

void solve() {
  int N, M, K;
  scanf("%d %d %d", &N, &M, &K);

  vector<int> cs(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &cs[i]);
  }

  UnionFindSet ufs(N);
  for (int i = 0; i < M; ++i) {
    int a, b;
    scanf("%d %d", &a, &b);
    ufs.merge(a-1, b-1);
  }
  
  vector<int> sizes;
  vector<int> counts;
  unordered_map<int, int> group_id;
  for (int i = 0, j = 0; i < N; ++i) {
    int g = ufs.find(i);
    auto it = group_id.find(g);
    if (it == group_id.end()) {
      group_id[g] = j++;
      sizes.push_back(1);
      counts.push_back(cs[i]);
    }
    else {
      sizes[it->second] += 1;
      counts[it->second] += cs[i];
    }
  }

  int ans = knapsack(sizes.size(), K-1, sizes, counts);
  printf("%d\n", ans);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
