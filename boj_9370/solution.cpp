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

void solution() {
	int n, m, t;
	scanf("%d %d %d", &n, &m, &t);
	
	int s, g, h;
	scanf("%d %d %d", &s, &g, &h);
	
	vector<vector<Edge>> edges(n+1);
	for (int i = 0; i < m; ++i) {
		int a, b, d;
		scanf("%d %d %d", &a, &b, &d);
		edges[a].push_back({a, b, d});
		edges[b].push_back({b, a, d});
	}

	vector<int> xs(t);
	for (int i = 0; i < t; ++i) {
		scanf("%d", &xs[i]);
	}

	vector<int> trace;
	LL sg_dist = dijkstra(edges, s, g);
	LL sh_dist = dijkstra(edges, s, h);
	LL gh_dist = dijkstra(edges, g, h);

	sort(xs.begin(), xs.end());
	for (int x : xs) {
		LL sx_dist = dijkstra(edges, s, x);
		LL gx_dist = dijkstra(edges, g, x);
		LL hx_dist = dijkstra(edges, h, x);

		if (sx_dist == min(sg_dist+gh_dist+hx_dist, sh_dist+gh_dist+gx_dist)) {
			printf("%d ", x);
		}
	}
	printf("\n");
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		solution();
	}
	
	return 0;
}
