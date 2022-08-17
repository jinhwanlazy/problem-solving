#include <bits/stdc++.h>
using namespace std;

class CombinationsWithReplacement {
  int N_;
  int M_;
  vector<int> res_;

 public:
  CombinationsWithReplacement(int N, int M) : N_(N), M_(M), res_(M, 0) {
  }

  bool next() {
    if (res_.front() == N_-1) {
      return false;
    }

    auto it = res_.end();

    while (it > res_.begin() && *(--it) == N_ - 1)
      continue;
    (*it)++;
    while (++it != res_.end())
      *it = *(it - 1);
    return true;
  }

  const vector<int>& get() const { return res_; }
};

void solve() {
  int N, M;
  scanf("%d %d", &N, &M);

  vector<int> xs(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &xs[i]);
  }

  sort(xs.begin(), xs.end());

  vector<vector<int>> res;
  CombinationsWithReplacement combi(N, M);
  do {
    vector<int> tmp;
    auto idxs = combi.get();
    for (int i : combi.get()) {
      tmp.push_back(xs[i]);
    }
    res.push_back(tmp);
  } while(combi.next());

  sort(res.begin(), res.end());

  vector<int> prv;
  for (const auto& seq : res) {
    if (seq == prv) {
      continue;
    }
    for (int i = 0; i < seq.size(); ++i) {
      printf("%d ", seq[i]);
    }
    printf("\n");
    prv = seq;
  }
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
