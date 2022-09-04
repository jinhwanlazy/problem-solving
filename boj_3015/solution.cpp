#include <bits/stdc++.h>
#include <cstdio>
using namespace std;

using LL = long long;

struct Stack {
  int data_[500001];
  int top_ = 0;
  
  void push(int x) {
    data_[top_++] = x;
  }

  int pop() {
    return data_[--top_];
  }

  int top() { 
    return data_[top_-1];
  }

  bool empty() const { 
    return top_ == 0;
  }

  int size() const {
    return top_;
  }

  int find(int x) const {
    int i = lower_bound(data_, data_ + top_, x, [](int lhs, int rhs) -> bool { return lhs > rhs; }) - data_;
    return i;
  }

  int find2(int x) const {
    int i = lower_bound(data_, data_ + top_, x, [](int lhs, int rhs) -> bool { return lhs >= rhs; }) - data_;
    return i;
  }
};

void solve() {
  int N;
  scanf("%d", &N);

  LL ans = 0;
  Stack S;
  
  for (int i = 0; i < N; ++i) {
    int h;
    scanf("%d", &h);
    if (S.empty()) {
      S.push(h);
      continue;
    } else {
      int p = S.find(h);
      int q = S.find2(h);
      ans += S.size() - p;
      ans += p > 0;
      S.top_ = q;
    }
    S.push(h);
  }
  printf("%lld\n", ans);
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
