#include <bits/stdc++.h>
using namespace std;

struct SequenceGenerator {
  struct promise_type {
    using Handle = coroutine_handle<promise_type>;
    SequenceGenerator get_return_object() { return SequenceGenerator{Handle::from_promise(*this)}; }
    suspend_always initial_suspend() { return {}; }
    suspend_always final_suspend() noexcept { return {}; }
    suspend_always yield_value(vector<int> sequence) {
      current_sequence = sequence;
      return {};
    }
    void unhandled_exception() {}
    vector<int> current_sequence;
  };

  explicit SequenceGenerator(promise_type::Handle coro) : coro_(coro) {}
  ~SequenceGenerator() {
    if (coro_)
      coro_.destroy();
  }
  vector<int> next() {
    coro_.resume();
    return coro_.promise().current_sequence;
  }

 private:
  promise_type::Handle coro_;
};

SequenceGenerator combinations(size_t n, size_t m, bool replacement=false) {
  stack<vector<int>> st;
  for (int i = n-1; i >= 0; --i) {
    st.push({i});
  }
  while (!st.empty()) {
    vector<int> sequence = st.top(); st.pop();
    if (sequence.size() == m) {
      co_yield sequence;
      continue;
    }
    int minVal = replacement ? sequence.back() : sequence.back() + 1;
    for (int i = n-1; i >= minVal; --i) {
      sequence.push_back(i);
      st.push(sequence);
      sequence.pop_back();
    }
  }
  co_yield {};
}

void solve() {
  int N, M;
  scanf("%d %d", &N, &M);

  vector<int> xs(N);
  for (int i = 0; i < N; ++i) {
    scanf("%d", &xs[i]);
  }
  sort(xs.begin(), xs.end());
  auto combi = combinations(N, M, true);
  for (auto s = combi.next(); !s.empty(); s = combi.next()) {
    for (auto i : s) {
      printf("%d ", xs[i]);
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
