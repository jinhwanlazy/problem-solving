#include <bits/stdc++.h>
#include <cstdlib>
using namespace std;

struct Bucket {
  Bucket(const vector<int>& arr) : arr_(arr), sorted_(arr) {
    sort(sorted_.begin(), sorted_.end());
  }

  void update(int i, int v) {
    if (arr_[i] != v) {
      int before = arr_[i];
      sorted_.erase(lower_bound(sorted_.begin(), sorted_.end(), before));
      arr_[i] = v;
      sorted_.insert(lower_bound(sorted_.begin(), sorted_.end(), v), v); 
    }
  }

  int query(int k) {
    return sorted_.end() - upper_bound(sorted_.begin(), sorted_.end(), k);
  }

  int query(int l, int r, int k) {
    if (l == 0 && r == arr_.size()-1) {
      return query(k);
    }
    int ans = 0;
    for (int i = l; i <= r; ++i) {
      ans += (int)(arr_[i] > k);
    }
    return ans;
  }
  
  vector<int> arr_;
  vector<int> sorted_;
};


void solve() {
  int N;
  scanf("%d", &N);

  int maxVal = 0;
  vector<int> A(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &A[i]);
    maxVal = max(maxVal, A[i]);
  }

  //int sqrtN = sqrt((double)N) + 1;
  int sqrtN = 1000;
  vector<Bucket> buckets;
  for (int l = 0; l < N; l += sqrtN) {
    int r = min(N, l + sqrtN);
    vector<int> partial(A.begin() + l, A.begin() + r);
    buckets.emplace_back(partial);
  }

  int K;
  scanf("%d", &K);
  while (K--) {
    int Q;
    scanf("%d", &Q);
    if (Q == 1) {
      int i, v;
      scanf("%d %d", &i, &v);
      i--;
      auto& bucket = buckets[i / sqrtN];
      bucket.update(i % sqrtN, v);
    } else {
      int i, j, k;
      scanf("%d %d %d", &i, &j, &k);
      int ans = 0;
      for (int l = 0; l < N; l += sqrtN) {
        int ii = i - 1 - l;
        int jj = j - 1 - l;
        if (jj < 0 || sqrtN <= ii) {
          continue;
        }
        ii = max(0, ii);
        jj = min(sqrtN-1, jj);
        ans += buckets[l / sqrtN].query(ii, jj, k);
      }
      printf("%d\n", ans);
    }
  }
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
