#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;
using LL = long long;
constexpr static int INF = numeric_limits<int>::max();

constexpr static int di[4] = {0, 0, -1, +1};
constexpr static int dj[4] = {-1, +1, 0, 0};

inline bool boundCheck(int i, int max_i) {
  return 0 <= i && i < max_i;
}

inline bool boundCheck2d(int i, int j, int max_i, int max_j) {
  return boundCheck(i, max_i) && boundCheck(j, max_j);
}

class Coord {
public:
  int x;
  int y;

  int sqDist(const Coord& other) const {
    return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
  }

  int coordId() const {
    return 20 * x + y;
  }

  static int coordId(int i, int j) {
    return Coord{j, i}.coordId();
  }
};

class Shark: public Coord {
public:
  int size;
};

class BabyShark: public Shark {
public:
  int age;
  int exp;

  bool updateLv() {
    if (exp >= size) {
      exp -= size; 
      size += 1;
      return true;
    }
    return false;
  }

  void moveAndEat(const shared_ptr<Shark>& prey, int distance) {
    x = prey->x;
    y = prey->y;
    age += distance;
    exp += 1;
  }
};

struct State {
  int u;
  LL cost;

  friend bool operator<(const State& lhs, const State& rhs) {
    return lhs.cost > rhs.cost;
  }
};

struct Edge {
  int u;
  int v;
  LL cost;
};

vector<LL> dijkstra(const vector<vector<Edge>>& edges, int src, vector<int> *trace=nullptr) {
  vector<LL> cost(edges.size(), INF);
  if (trace) {
    trace->resize(edges.size());
    fill(trace->begin(), trace->end(), -1);
  }
  priority_queue<State> Q;
  cost[src] = 0;
  Q.push({src, 0});
  while (!Q.empty()) {
    auto [u, c] = Q.top(); Q.pop();
    if (cost[u] < c) {
      continue;
    }
    for (const auto& [_, v, w] : edges[u]) {
      int next_cost = c + w;
      if (next_cost < cost[v]) {
        cost[v] = next_cost;
        Q.push({v, next_cost});
        if (trace) {
          (*trace)[v] = u;
        }
      }
    }
  }
  return cost;
}

class Sim {
  int N_;
  vector<vector<shared_ptr<Shark>>> world_;
  shared_ptr<BabyShark> baby_;

 public:
  
  Sim(int N) : N_(N) {
    initialize();
  }

  int run() {
    while (true) {
      vector<shared_ptr<Shark>> edibles;
      vector<vector<Edge>> graph;
      buildGraph(graph, edibles);
      if (edibles.empty()) {
        break;
      }
      auto costs = dijkstra(graph, baby_->coordId());
      auto prey =
          *min_element(edibles.begin(), edibles.end(),
                       [&costs](const auto& lhs, const auto& rhs) -> bool {
                         return costs[lhs->coordId()] < costs[rhs->coordId()];
                       });
      int cost = costs[prey->coordId()];
      if (cost == INF) {
        break;
      }
      world_[prey->y][prey->x] = baby_;
      world_[baby_->y][baby_->x] = nullptr;
      baby_->moveAndEat(prey, cost);
      baby_->updateLv();
      
    }
    return baby_->age;
  }

 private:
  void initialize() {
    readWorld();
  }

  void readWorld() {
    world_.resize(N_);
    for (int i = 0; i < N_; ++i) {
      auto& row = world_[i];
      row.resize(N_, nullptr);
      for (int j = 0; j < N_; ++j) {
        auto& shark = row[j];
        int size;
        scanf("%d", &size);
        if (size == 9) {
          baby_ = make_shared<BabyShark>();
          baby_->size = 2;
          shark = baby_;
        }
        else if (0 < size && size <= 6) {
          shark = make_shared<Shark>();
          shark->size = size;
        }
        if (shark != nullptr) {
          shark->x = j;
          shark->y = i;
        }
      }
    }
  }

  void buildGraph(vector<vector<Edge>>& graph, vector<shared_ptr<Shark>>& edibles) {
    graph.resize(400);
    for (int i = 0; i < N_; ++i) {
      for (int j = 0; j < N_; ++j) {
        const shared_ptr<Shark>& prey = world_[i][j];
        if (prey != nullptr) {
          if (prey->size < baby_->size) {
            edibles.push_back(prey);
          }
        }
        for (int k = 0; k < 4; ++k) {
          const int ii = i + di[k];
          const int jj = j + dj[k];
          if (!boundCheck2d(ii, jj, N_, N_)) {
            continue;
          }
          const shared_ptr<Shark>& prey2 = world_[ii][jj];
          if (prey2 == nullptr || prey2->size <= baby_->size) {
            int u = Coord::coordId(i, j);
            int v = Coord::coordId(ii, jj);
            graph[u].push_back({u, v, 1});
          }
        }
      }
    }
  }
};

int main() {
  int N;
  scanf("%d", &N);

  Sim sim(N);
  int ans = sim.run();

  printf("%d\n", ans);

  return 0;
}
