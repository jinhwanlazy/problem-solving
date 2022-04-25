#include <bits/stdc++.h> 
using namespace std;

using LL = long long;
constexpr static int INF = numeric_limits<int>::max();

struct State {
	int u;
	int cost;

	friend bool operator<(const State& lhs, const State& rhs) {
		return lhs.cost > rhs.cost;
	}
};

struct Edge {
	int u;
	int v;
	int cost;
};

LL dijkstra(const vector<vector<Edge>>& edges, int src, int dst) {
	vector<int> cost(edges.size(), INF);
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
			}
		}
	}
	return cost[dst];
}

int main()
{
	int MAX = 100000;
	
	int N, K;
	scanf("%d %d", &N, &K);
	
	vector<vector<Edge>> edges(MAX+1);
	int n_edges = 0;
	for (int i = 0; i <= MAX; ++i) {
		if (i > 0) {
			edges[i].push_back({i, i-1, 1});
			for (int j = i*2; j <= MAX; j *= 2) {
				edges[i].push_back({i, j, 0});
			}
		}
		if (i < MAX) {
			edges[i].push_back({i, i+1, 1});
		}
		n_edges += edges[i].size();
	}
	
	LL ans = dijkstra(edges, N, K);
	printf("%lld\n", ans);
	
	return 0;
}
