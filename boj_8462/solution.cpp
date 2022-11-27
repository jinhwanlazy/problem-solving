#include <bits/stdc++.h>
using namespace std;

static constexpr int bucketSize = 100;
using LL = long long;

struct Query {
  int l;
  int r;
  int index;
  int bIndex;
  LL result;
};

struct Power {
  int K_[1000001];
  LL res_ = 0;
  
  void insert(int a) {
    res_ -= (LL)get(a);
    K_[a]++;
    res_ += (LL)get(a);
  }

  void erase(int a) {
    res_ -= (LL)get(a);
    K_[a]--;
    res_ += (LL)get(a);
  }

  LL get(int a) {
    return (LL)K_[a] * (LL)K_[a] * (LL)a;
  }

  LL get() {
    return res_;
  }

  void clear() {
    fill(K_, K_ + 1000001, 0);
    res_ = 0;
  }
};

void solve() {
  int n, t;
  scanf("%d %d", &n, &t);
  
  vector<int> A(n+1);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &A[i]);
  }

  vector<Query> queries;
  queries.reserve(t);
  for (int i = 0; i < t; ++i) {
    int l, r;
    scanf("%d %d", &l, &r);
    queries.push_back({l, r, i, l / bucketSize, -1});
  }

  sort(queries.begin(), queries.end(),
       [](const auto& q1, const auto& q2) -> bool {
         if (q1.bIndex == q2.bIndex)
           return q1.r < q2.r;
         return q1.bIndex < q2.bIndex;
       });


  Power p;

  int l = 0;
  int r = 0;
  p.insert(0);
  for (auto& q : queries) {
    if (l == -1) {
      p.clear();
      l = q.l;
      r = q.r;
      for (int i = l; i <= r; ++i) {
        p.insert(A[i]);
      }
      q.result = p.get();
    }
    else {
      while (r < q.r) p.insert(A[++r]);
      while (q.r < r) p.erase(A[r--]);
      while (q.l < l) p.insert(A[--l]);
      while (l < q.l) p.erase(A[l++]);
      q.result = p.get();
    }
  }

  sort(queries.begin(), queries.end(),
       [](const auto& q1, const auto& q2) -> bool {
         return q1.index < q2.index;
       });

  for (const auto& q : queries) {
    printf("%lld\n", q.result);
  }
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
