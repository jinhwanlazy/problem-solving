#include <bits/stdc++.h>
using namespace std;

using LL = long long;

struct State {
  int e = 0;
  vector<int> s = {};

  vector<int> count(int W) {
    vector<int> res(W, 0);
    for (int w : s) {
      res[w]++;
    }
    return res;
  }

  friend bool operator<(const State& lhs, const State& rhs) { return true; }

  static bool should_pop(const vector<int> current_count,
                         const vector<int>& target) {
    for (int i = 0; i < target.size(); ++i) {
      if (current_count[i] > target[i]) {
        return true;
      }
    }
    return false;
  }

  friend ostream& operator<<(ostream& os, const State& s) {
    os << "State(e=" << s.e << ", s: ";
    for (int i = 0; i < s.s.size(); ++i) {
      os << s.s[i];
      if (i < s.s.size() - 1) {
        os << " ";
      }
    }
    os << ")";
    return os;
  }

  size_t operator()(const State& s) const noexcept {
    size_t seed = vec.size();
    for (auto& i : vec) {
      seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
  }
};

namespace std {
template <>
struct hash<State> {
  std::size_t operator()(const State& s) const noexcept { return s(s); }
};
}  // namespace std

// LL solution(const vector<vector<int>>& es)
//{
// int W = es[0].size();
// priority_queue<pair<int, State>> pq;
// pq.push({0, State{0, {}}});

// unordered_set<State> visited;

// while (!pq.empty()) {
// auto p_state = pq.top();
// pq.pop();
// int distance = p_state.first;
// auto state = p_state.second;
// if (visited.find(state) != visited.end()) {
// continue;
//}
// visited.insert
// const auto& target = es[state.e];
// cout << state.e << ", " << state << "\n";
// if (state.e == es.size()) {
// return distance + state.s.size();
//}
// vector<int> count = state.count(W);
// if (count == target) {
// state.e++;
// pq.push({distance, state});
//}
// else if (State::should_pop(count, target)) {
// state.s.pop_back();
// pq.push({distance+1, state});
//}
// else {
// for (int i = 0; i < target.size(); ++i) {
// if (count[i] < target[i]) {
// state.s.push_back(i);
// pq.push({distance+1, state});
// state.s.pop_back();
//}
//}
//}
//}

// return -1;
//}

size_t sum(const vector<int>& es) {
  size_t res(0);
  for (auto e : es) {
    res += e;
  }
  return res;
}

size_t sum(const vector<vector<int>>& es) {
  size_t res(0);
  for (const auto& e : es)
    res += sum(e);
  return res;
}

vector<int> get_common(const vector<int>& a, const vector<int>& b) {
  vector<int> res(a.size(), 0);
  for (int i = 0; a.size(); ++i) {
    res[i] = min()
  }
}

LL solution(const vector<vector<int>>& es, int W) {
  if (es.size() == 0) {
    return 0;
  }
  if (es.size() == 1) {
    return sum(es) * 2;
  }
  if (sum(es) == 0) {
    return 0;
  }
  vector<int> maxCommon = es[0];
  for (int i = 1; i < es.size(); ++i) {
  }
}

int main() {
  int T;
  cin >> T;
  for (int i = 1; i <= T; ++i) {
    int E, W;
    cin >> E >> W;
    vector<vector<int>> es(E);
    for (int i = 0; i < E; ++i) {
      es[i].resize(W);
      for (int j = 0; j < W; ++j) {
        cin >> es[i][j];
      }
    }
    cout << "Case #" << i << ": " << solution(es) << "\n";
  }
  return 0;
}
