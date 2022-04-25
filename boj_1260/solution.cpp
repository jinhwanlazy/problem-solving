#include <bits/stdc++.h> 
using namespace std;

int main()
{
	int N, M, V;
	scanf("%d %d %d", &N, &M, &V);
	
	vector<vector<int>> edges(N+1);
	for (int i = 0; i < M; ++i) {
		int a, b;
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	for (auto& es : edges) {
		sort(es.begin(), es.end(), [](int l, int r){ return r < l; });
	}

	vector<bool> dfs_visited(N+1, false);
	vector<int> dfs_history;
	vector<int> S{V};
	while (!S.empty()) {
		int u = S.back(); S.pop_back();
		if (dfs_visited[u]) {
			continue;
		}
		dfs_history.push_back(u);
		dfs_visited[u] = true;
		for (int v : edges[u]) {
			if (!dfs_visited[v]) {
				S.push_back(v);
			}
		}
	}
	for (int i = 0; i < dfs_history.size(); ++i) {
		printf("%d ", dfs_history[i]);
	}
	printf("\n");

	for (auto& es : edges) {
		sort(es.begin(), es.end(), [](int l, int r){ return l < r; });
	}
	vector<bool> bfs_visited(N+1, false);
	vector<int> bfs_history;
	deque<int> Q{V};
	while (!Q.empty()) {
		int u = Q.front(); Q.pop_front();
		if (bfs_visited[u]) {
			continue;
		}
		bfs_history.push_back(u);
		bfs_visited[u] = true;
		for (int v : edges[u]) {
			if (!bfs_visited[v]) {
				Q.push_back(v);
			}
		}
	}
	for (int i = 0; i < bfs_history.size(); ++i) {
		printf("%d ", bfs_history[i]);
	}
	
	
	return 0;
}
