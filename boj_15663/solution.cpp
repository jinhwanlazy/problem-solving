#include <bits/stdc++.h>
using namespace std;

class Permutations {
  int N_;
  int M_;
  vector<int> arr_;
  vector<int> res_;

 public:
  Permutations(int N, int M) : N_(N), M_(M), arr_(N), res_(M_) {
    iota(arr_.begin(), arr_.end(), 0);
    iota(res_.begin(), res_.end(), 0);
  }

  // https://stackoverflow.com/a/61402151
  bool next_partial_permutation(std::vector<int>::iterator beg,
                                std::vector<int>::iterator mid,
                                std::vector<int>::iterator end) {
    if (beg == mid) {
      return false;
    }
    if (mid == end) {
      return std::next_permutation(beg, end);
    }

    auto p1 = mid;

    while (p1 != end && !(*(mid - 1) < *p1))
      ++p1;

    if (p1 != end) {
      std::swap(*p1, *(mid - 1));
      return true;
    } else {
      std::reverse(mid, end);
      auto p3 = std::make_reverse_iterator(mid);

      while (p3 != std::make_reverse_iterator(beg) && !(*p3 < *(p3 - 1)))
        ++p3;

      if (p3 == std::make_reverse_iterator(beg)) {
        std::reverse(beg, end);
        return false;
      }

      auto p2 = end - 1;

      while (!(*p3 < *p2))
        --p2;

      std::swap(*p3, *p2);
      std::reverse(p3.base(), end);
      return true;
    }
  }

  bool next() {
    bool success = next_partial_permutation(arr_.begin(), arr_.begin() + M_, arr_.end());
    if (!success) {
      return false;
    }
    copy(arr_.begin(), arr_.begin() + M_, res_.begin());
    return true;
  }

  const vector<int>& get() const {
    return res_;
  }
};

void solve() {
  int N, M;
  scanf("%d %d", &N, &M);

  vector<int> xs(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &xs[i]);
  }
  sort(xs.begin(), xs.end());

  vector<vector<int>> ans;
  Permutations P(N, M);
  do {
    vector<int> idxs = P.get();
    vector<int> res(M);
    for (int i = 0; i < M; ++i) {
      res[i] = xs[idxs[i]];
    }
    ans.push_back(res);
  } while (P.next());

  sort(ans.begin(), ans.end());
  
  vector<int> prev;
  for (const auto& seq : ans) {
    if (seq == prev) {
      continue;
    }
    prev = seq;
    for (size_t i = 0; i < seq.size(); ++i) {
      printf("%d ", seq[i]);
    }
    printf("\n");
  }

}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
