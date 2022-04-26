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
	int M = 100000;

	vector<vector<Edge>> edges(M+1);
	for (int i = 0; i <= M; ++i) {
		if (i > 0) {
			edges[i].push_back({i, i-1, 1});
			if (i % 2 == 0) {
				edges[i].push_back({i, i/2, 1});
			}
		}
		if (i < M) {
			edges[i].push_back({i, i+1, 1});
		}
	}

	int N, K;
	scanf("%d %d", &N, &K);

	vector<int> trace;
	auto cost = dijkstra(edges, K, &trace);

	printf("%lld\n", cost[N]);
	while (N != K) {
		printf("%d ", N);
		N = trace[N];
	}
	printf("%d\n", K);
	
	
	return 0;
}
