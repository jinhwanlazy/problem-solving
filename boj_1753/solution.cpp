#include <bits/stdc++.h> 
using namespace std;

struct State {
	int u;
	int cost;

	friend bool operator<(const State& lhs, const State& rhs) {
		return lhs.cost > rhs.cost;
	}
};

int main()
{
	constexpr static int INF = numeric_limits<int>::max();
	
	int V, E;
	scanf("%d %d", &V, &E);
	
	int K;
	scanf("%d", &K);
	
	vector<vector<pair<int, int>>> edges(V+1);
	for (int i = 0; i < E; ++i) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		edges[u].push_back({v, w});
	}

	vector<int> cost(V+1, INF);
	priority_queue<State> Q;
	cost[K] = 0;
	Q.push({K, 0});
	while (!Q.empty()) {
		auto [u, c] = Q.top(); Q.pop();
		if (cost[u] < c) {
			continue;
		}

		for (const auto& [v, w] : edges[u]) {
			int next_cost = c + w;
			if (next_cost < cost[v]) {
				cost[v] = next_cost;
				Q.push({v, next_cost});
			}
		}
	}

	for (int i = 1; i <= V; ++i) {
		if (cost[i] != INF) {
			printf("%d\n", cost[i]);
		}
		else {
			printf("INF\n");
		}
	}

	return 0;
}
