#include <bits/stdc++.h>
using namespace std;

struct UnionFindSet {
  UnionFindSet(int size) : data_(size), rank_(size, 0) {
    for (int i = 0; i < size; ++i) {
      data_[i] = i;
    }
  }

  int find(int i) {
    if (data_[i] == i) {
      return i;
    }
    int root = find(data_[i]);
    data_[i] = root;
    return root;
  }

  void merge(int i, int j) {
    int i_root = find(i);
    int j_root = find(j);
    if (i_root == j_root) {
      return;
    }
    if (rank_[i_root] == rank_[j_root]) {
      data_[i_root] = j_root;
      rank_[i_root]++;
    } else if (rank_[i_root] < rank_[j_root]) {
      data_[i_root] = j_root;
    } else {
      data_[j_root] = i_root;
    }
  }

  vector<int> data_;
  vector<int> rank_;
};

int main() {
  int N, M;
  scanf("%d %d", &N, &M);

  UnionFindSet uf(N + 1);

  for (int i = 0; i < M; ++i) {
    int cmd, a, b;
    scanf("%d %d %d", &cmd, &a, &b);

    if (cmd == 0) {
      uf.merge(a, b);
    } else {
      cout << (uf.find(a) == uf.find(b) ? "YES" : "NO") << "\n";
    }
  }
  return 0;
}
