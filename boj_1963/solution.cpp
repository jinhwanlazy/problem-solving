#include <bits/stdc++.h>
using namespace std;

struct Sieve {
  Sieve(size_t max_size) : data_(max_size, true) {
    data_[0] = false;
    data_[1] = false;
    for (size_t i = 2; i < max_size; ++i) {
      if (!data_[i]) {
        continue;
      }
      for (size_t j = i * 2; j < max_size; j += i) {
        data_[j] = false;
      }
    }
  }
  
  bool isPrime(size_t i) {
    return data_[i];
  }
  
  vector<bool> data_;
};

class Dijkstra {
 public:
  using cost_t = int;
  static constexpr cost_t INF = numeric_limits<cost_t>::max();

  struct State {
    int u;
    cost_t cost;

    friend bool operator<(const State& lhs, const State& rhs) { return lhs.cost > rhs.cost; }
  };

  struct Edge {
    int u;
    int v;
    cost_t cost;
  };

 public:
  const vector<vector<Edge>>& graph_;
  vector<cost_t> costs_;
  vector<int> trace_;

  int src_;
  int dst_ = -1;
  bool doTrace_ = false;

 public:
  Dijkstra(const vector<vector<Edge>>& adjListGraph, int src = 0)
      : graph_(adjListGraph), costs_(adjListGraph.size()), trace_(0), src_(src) {}

  void setDoTrace() { doTrace_ = true; }
  void setSrc(int src) { src_ = src; }
  void setDst(int dst) { dst_ = dst; }
  const vector<cost_t>& cost() const { return costs_; }
  const vector<int>& trace() const { return trace_; }

  void solve() {
    if (src_ == -1) {
      throw runtime_error("src is not defined!");
    }
    fill(costs_.begin(), costs_.end(), INF);
    if (doTrace_) {
      trace_.resize(costs_.size());
      fill(trace_.begin(), trace_.end(), -1);
    }

    priority_queue<State> pq;
    costs_[src_] = 0;
    pq.push({src_, 0});
    while (!pq.empty()) {
      auto [u, c] = pq.top();
      pq.pop();
      if (costs_[u] < c) {
        continue;
      }
      if (u == dst_) {
        break;
      }
      for (const auto& [_, v, w] : graph_[u]) {
        cost_t nextCost = c + w;
        if (nextCost < costs_[v]) {
          costs_[v] = nextCost;
          pq.push({v, nextCost});
          if (doTrace_) {
            trace_[v] = u;
          }
        }
      }
    }
  }
};

void solve() {
  Sieve sieve(10000);
  vector<int> primeIndex(10000, -1);
  vector<int> primes;
  for (int i = 1000; i < 10000; ++i) {
    if (sieve.isPrime(i)) {
      primeIndex[i] = primes.size();
      primes.push_back(i);
    }
  }

  vector<vector<Dijkstra::Edge>> graph(primes.size());

  for (int p : primes) {
    int a = p / 1000;
    int b = (p % 1000) / 100;
    int c = (p % 100) / 10;
    int d = p % 10;
    for (int i = 1; i < 10; ++i) {
      if (i != a) {
        int q = 1000 * i + 100 * b + 10 * c + d;
        if (primeIndex[q] != -1) {
          graph[primeIndex[p]].push_back({primeIndex[p], primeIndex[q], 1});
          graph[primeIndex[q]].push_back({primeIndex[q], primeIndex[p], 1});
        }
      }
    }
    for (int i = 0; i < 10; ++i) {
      if (i != b) {
        int q = 1000 * a + 100 * i + 10 * c + d;
        if (primeIndex[q] != -1) {
          graph[primeIndex[p]].push_back({primeIndex[p], primeIndex[q], 1});
          graph[primeIndex[q]].push_back({primeIndex[q], primeIndex[p], 1});
        }
      }
    }
    for (int i = 0; i < 10; ++i) {
      if (i != c) {
        int q = 1000 * a + 100 * b + 10 * i + d;
        if (primeIndex[q] != -1) {
          graph[primeIndex[p]].push_back({primeIndex[p], primeIndex[q], 1});
          graph[primeIndex[q]].push_back({primeIndex[q], primeIndex[p], 1});
        }
      }
    }
    for (int i = 0; i < 10; ++i) {
      if (i != d) {
        int q = 1000 * a + 100 * b + 10 * c + i;
        if (primeIndex[q] != -1) {
          graph[primeIndex[p]].push_back({primeIndex[p], primeIndex[q], 1});
          graph[primeIndex[q]].push_back({primeIndex[q], primeIndex[p], 1});
        }
      }
    }
  }

  int N;
  scanf("%d", &N);
  for (int i = 0; i < N; ++i) {
    int p, q;
    scanf("%d %d", &p, &q);

    Dijkstra dijk(graph, primeIndex[p]);
    dijk.setDst(primeIndex[q]);
    dijk.solve();

    printf("%d\n", dijk.cost()[primeIndex[q]]);
  }
}

int main() {
  int T = 1;
  while (T--) {
    solve();
  }

  return 0;
}
