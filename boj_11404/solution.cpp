#include <bits/stdc++.h> 
using namespace std;

using LL = long long;
constexpr static LL INF = numeric_limits<int>::max();

vector<vector<LL>> floydWarshall(const vector<vector<LL>>& adj) {
	size_t N = adj.size()-1;
	auto cost = adj;

	for (int k = 1; k <= N; ++k) {
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				if (cost[i][k] != INF && cost[k][j] != INF) {
					cost[i][j] = min(cost[i][k] + cost[k][j], cost[i][j]);
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
	
	vector<vector<LL>> adj(N+1, vector<LL>(N+1, INF));
	for (int i = 0; i < M; ++i) {
		int A, B, C;
		scanf("%d %d %d", &A, &B, &C);
		adj[A][B] = min(adj[A][B], (LL)C);
	}
	for (int i = 1; i <= N; ++i) {
		adj[i][i] = 0;
	}
	auto cost = floydWarshall(adj);
	for (int i = 1; i < cost.size(); ++i) {
		for(int j = 1; j < cost[i].size(); ++j) {
			printf("%lld ", cost[i][j] == INF ? 0 : cost[i][j]);
		}
		printf("\n");
	}
	return 0;
}
