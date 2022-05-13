#include <bits/stdc++.h>
using namespace std;

using LL = long long;

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
    for (int i = size_before; i < size; ++i) {
      root_[i] = i;
    }
    return true;
  }

  size_t size() const { return root_.size(); }

  vector<int> root_;
  vector<int> rank_;
  vector<int> size_;
};

struct Edge {
  int u;
  int v;
  int w; /* cost */

  friend bool operator<(const Edge& lhs, const Edge& rhs) {
    return lhs.w > rhs.w;
  }
};

int main() {
  int N, M;
  scanf("%d %d", &N, &M);

  priority_queue<Edge> pq;
  for (int i = 0; i < M; ++i) {
    int A, B, C;
    scanf("%d %d %d", &A, &B, &C);
    A--;
    B--;

    pq.push({A, B, C});
  }
  LL ans = 0;
  LL last = 0;
  UnionFindSet ufs(N);
  while (!pq.empty()) {
    auto [A, B, C] = pq.top();
    pq.pop();
    if (ufs.find(A) == ufs.find(B)) {
      continue;
    }
    ufs.merge(A, B);
    ans += (LL)C;
    last = (LL)C;
  }
  ans -= last;
  // set<int> unique;
  // for (int i = 0; i < N; ++i) {
  // unique.insert(ufs.find(i));

  //}
  printf("%lld\n", ans);

  return 0;
}
