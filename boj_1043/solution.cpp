#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

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

int main() {
  int N, M;
  scanf("%d %d", &N, &M);
  
  int nWitness;
  scanf("%d", &nWitness);
  vector<int> ws(nWitness);
  for (int i = 0; i < nWitness; ++i) {
    scanf("%d", &ws[i]);
    ws[i]--;
  }

  vector<vector<int>> parties(M);
  UnionFindSet ufs(N);
  for (int i = 0; i < M; ++i) {
    int partySize;
    scanf("%d", &partySize);

    auto& party = parties[i];
    party.resize(partySize);
    for (int i = 0; i < partySize; ++i) {
      scanf("%d", &party[i]);
      party[i]--;
    }
    for (int j = 0; j < partySize-1; ++j) {
      for (int k = j+1; k < partySize; ++k) {
        ufs.merge(party[j], party[k]);
      }
    }
  }

  set<int> contaminatedParties;
  for (int w : ws) {
    contaminatedParties.insert(ufs.find(w));
  }

  int ans = 0;
  for (int i = 0; i < M; ++i) {
    auto& party = parties[i];
    bool contaminated = false;
    for (int mem : party) {
      if (contaminatedParties.find(ufs.find(mem)) != contaminatedParties.end()) {
        contaminated = true;
        break;
      }
    }
    if (!contaminated) {
      ans += 1;
    }
  }
  printf("%d\n", ans);
  return 0;
}
