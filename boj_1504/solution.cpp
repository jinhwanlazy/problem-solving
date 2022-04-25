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
	int V, E;
	scanf("%d %d", &V, &E);
	
	vector<vector<Edge>> edges(V+1);
	for (int i = 0; i < E; ++i) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		edges[u].push_back(Edge{u, v, w});
		edges[v].push_back(Edge{v, u, w});
	}

	int v1, v2;
	scanf("%d %d", &v1, &v2);
	
	LL d1 = 0;
	LL d2 = 0;

	d1 += dijkstra(edges, 1, v1);
	d1 += dijkstra(edges, v1, v2);
	d1 += dijkstra(edges, v2, V);

	d2 += dijkstra(edges, 1, v2);
	d2 += dijkstra(edges, v2, v1);
	d2 += dijkstra(edges, v1, V);

	if (d1 >= INF && d2 >= INF) {
		printf("-1\n");
	}
	else if (d1 >= INF) {
		printf("%lld\n", d2);
	}
	else if (d2 >= INF) {
		printf("%lld\n", d1);
	}
	else {
		printf("%lld\n", min(d1, d2));
	}

	return 0;
}
