#include <bits/stdc++.h> 
using namespace std;

using LL = long long;
constexpr static int INF = numeric_limits<int>::max();

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

int main()
{
	int N, M;
	scanf("%d %d", &N, &M);
	
	vector<vector<Edge>> edges(N+1);
	for (int i = 0; i < M; ++i) {
		int A, B, C;
		scanf("%d %d %d", &A, &B, &C);
		edges[A].push_back({A, B, C});
	}

	int src, dst;
	scanf("%d %d", &src, &dst);

	vector<int> trace;
	auto cost = dijkstra(edges, src, &trace);

	printf("%lld\n", cost[dst]);
	
	vector<int> ans;
	while (dst != src) {
		ans.push_back(dst);
		dst = trace[dst];
	}
	ans.push_back(src);

	printf("%ld\n", ans.size());
	for (auto it = ans.rbegin(); it != ans.rend(); ++it) {
		printf("%d ", *it);
	}
	printf("\n");
	
	return 0;
}
