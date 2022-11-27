#include <bits/stdc++.h>
using namespace std;

constexpr int batchSize = 1000;

struct Query {
  int l;
  int r;
  int index;
  int bIndex;
  int result;
};

struct Counter {
  int counter_[1000001];
  int counter2_[1000001];
  int res_ = 0;

  void push(int a) {
    counter2_[counter_[a]]--;
    counter_[a]++;
    counter2_[counter_[a]]++;
    if (counter2_[counter_[a]] == 1) {
      res_ = max(res_, counter_[a]);
    }
  }

  void pop(int a) {
    counter2_[counter_[a]]--;
    counter_[a]--;
    counter2_[counter_[a]]++;
    while (counter2_[res_] == 0 && res_ > 0) {
      res_--;
    }
  }

  int get() const {
    return res_;
  }

  void clear() { 
    fill(counter_, counter_ + 1000001, 0);
    fill(counter2_, counter2_ + 1000001, 0);
    counter2_[0] = 1000000;
  }
};

void solve() {
  int N;
  scanf("%d", &N);
  
  vector<int> A(N+1);
  for (int i = 1; i <= N; ++i) {
    scanf("%d", &A[i]);
  }

  int M;
  scanf("%d", &M);
  

  vector<Query> Q(M);
  for (int i = 0; i < M; ++i) {
    int l, r;
    scanf("%d %d", &l, &r);
    Q[i] = {l, r, i, l / batchSize, -1};
  }

  sort(Q.begin(), Q.end(), [](const auto& q1, const auto& q2) -> bool {
    if (q1.bIndex == q2.bIndex) {
      return q1.r < q2.r;
    }
    return q1.bIndex < q2.bIndex;
  });

  Counter c;
  Query* prevQ = nullptr;
  for (Query& q : Q) {
    if (prevQ == nullptr/* || prevQ->bIndex != q.bIndex*/) {
      c.clear();
      for (int i = q.bIndex * batchSize; i <= q.r; ++i) {
        c.push(A[i]);
      }
      for (int i = q.bIndex * batchSize; i < q.l; ++i) {
        c.pop(A[i]);
      }
      q.result = c.get();
      //cout << "a\n";
    } else {
      if (q.r < prevQ->r) {
        for (int i = q.r+1; i <= prevQ->r; ++i) {
          c.pop(A[i]);
        }
      }
      else if (q.r > prevQ->r) {
        for (int i = prevQ->r + 1; i <= q.r; ++i) {
          c.push(A[i]);
        }
      }
      if (q.l < prevQ->l) {
        for (int i = q.l; i < prevQ->l; ++i) {
          c.push(A[i]);
        }
      }
      else if (q.l > prevQ->l) {
        for (int i = prevQ->l; i < q.l; ++i) {
          c.pop(A[i]);
        }
      }
      q.result = c.get();
    }
    prevQ = &q;
  }

  sort(Q.begin(), Q.end(), [](const auto& q1, const auto& q2) -> bool {
    return q1.index < q2.index;
  });

  for (const Query& q : Q) {
    printf("%d\n", q.result);
    
  }
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}

