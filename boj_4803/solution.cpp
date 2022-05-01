#include <bits/stdc++.h> 
using namespace std;

bool is_tree(
		const vector<vector<int>>& edges,
		vector<bool>& seen,
		vector<int>& parent,
		int src) {
	queue<int> Q;
	Q.push(src);

	bool res = true;
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		if (seen[u]) {
			continue;
		}
		seen[u] = true;
		for (int v : edges[u]) {
			if (seen[v]) {
				if (parent[u] != v) {
					res = false;
					//cout << u << ", " << v << "!!\n";
				}
			} 
			else {
				Q.push(v);
				parent[v] = u;
			}
		}
	}
	return res;
}

int main()
{
	int T = 0;
	while (true) {
		int N, M;
		scanf("%d %d", &N, &M);
		if (N == 0 && M == 0) {
			break;
		}

		vector<vector<int>> edges(N+1);
		for (int i = 0; i < M; ++i) {
			int u, v;
			scanf("%d %d", &u, &v);
			edges[u-1].push_back(v-1);
			edges[v-1].push_back(u-1);
		}
		
		vector<bool> seen(N, false);
		vector<int> parent(N, -1);
		int tree_count = 0;
		
		for (int u = 0; u < N; ++u) {
			if (seen[u]) {
				continue;
			}
			tree_count += is_tree(edges, seen, parent, u);
		}

		if (tree_count == 0) {
			printf("Case %d: No trees.\n", ++T);
		}
		else if (tree_count == 1) {
			printf("Case %d: There is one tree.\n", ++T);
		}
		else {
			printf("Case %d: A forest of %d trees.\n", ++T, tree_count);
		}
	}
	return 0;
}
