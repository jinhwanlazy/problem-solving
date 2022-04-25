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

	int N;
	scanf("%d", &N);
	
	int M;
	scanf("%d", &M);
	
	vector<vector<pair<int, int>>> edges(N+1);
	for (int i = 0; i < M; ++i) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		edges[u].push_back({v, w});
	}

	int A, B;
	scanf("%d %d", &A, &B);

	vector<int> cost(N+1, INF);
	vector<State> reserved;
	priority_queue<State> Q;

	cost[A] = 0;
	Q.push({A, 0});
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
	
	printf("%d\n", cost[B]);
	return 0;
}
