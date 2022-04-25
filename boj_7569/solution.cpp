#include <bits/stdc++.h> 
using namespace std;

inline bool boundCheck(int i, int max_i) {
	return 0 <= i && i < max_i;
}

inline bool boundCheck(int i, int min_i, int max_i) {
	return min_i <= i && i < max_i;
}

inline bool boundCheck3d(int i, int j, int k, int max_i, int max_j, int max_k) {
	return boundCheck(i, max_i) && boundCheck(j, max_j) && boundCheck(k, max_k);
}

inline bool boundCheck3d(int i, int j, int k, int min_i, int min_j, int min_k, int max_i, int max_j, int max_k) {
	return boundCheck(i, min_i, max_i) && boundCheck(j, min_j, max_j) && boundCheck(k, min_k, max_k);
}

int main()
{
	const static int di[6] = {0, 0, 0, 0, -1, 1};
	const static int dj[6] = {0, 0, -1, 1, 0, 0};
	const static int dk[6] = {-1, 1, 0, 0, 0, 0};
	int M, N, H;
	scanf("%d %d %d", &M, &N, &H);
	
	vector<vector<vector<int>>> grid(H, vector<vector<int>>(N, vector<int>(M, 0)));
	vector<vector<vector<bool>>> visited(H, vector<vector<bool>>(N, vector<bool>(M, false)));

	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < N; ++j) {
			for (int k = 0; k < M; ++k) {
				scanf("%d", &grid[i][j][k]);
			}
		}
	}
	queue<tuple<int, int, int, int>> Q;
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < N; ++j) {
			for (int k = 0; k < M; ++k) {
				if (grid[i][j][k] == 1) {
					Q.push({i, j, k, 0});
				}
			}
		}
	}

	int ans = 0;
	while (!Q.empty()) {
		auto& front = Q.front();
		int i = get<0>(front);
		int j = get<1>(front);
		int k = get<2>(front);
		int d = get<3>(front);
		Q.pop();
		if (visited[i][j][k]) {
			continue;
		}
		visited[i][j][k] = true;
		grid[i][j][k] = 1;
		ans = max(ans, d);
		for (int l = 0; l < 6; ++l) {
			int ii = i + di[l];
			int jj = j + dj[l];
			int kk = k + dk[l];
			if (boundCheck3d(ii, jj, kk, H, N, M) && grid[ii][jj][kk] == 0) {
				Q.push({ii, jj, kk, d+1});
			}
		}
	}
	
	for (int i = 0; i < H; ++i) {
		for (int j = 0; j < N; ++j) {
			for (int k = 0; k < M; ++k) {
				if (grid[i][j][k] == 0) {
					printf("-1\n");
					return 0;
				}
			}
		}
	}
	printf("%d\n", ans);
	
	return 0;
}
