#include <bits/stdc++.h> 
using namespace std;

bool boundCheck(int i, int max_i) {
	return 0 <= i && i < max_i;
}

bool boundCheck(int i, int min_i, int max_i) {
	return min_i <= i && i < max_i;
}

bool boundCheck2d(int i, int j, int max_i, int max_j) {
	return boundCheck(i, max_i) && boundCheck(j, max_j);
}

bool boundCheck2d(int i, int j, int min_i, int min_j, int max_i, int max_j) {
	return boundCheck(i, min_i, max_i) && boundCheck(j, min_j, max_j);
}

int main()
{
	const static int di[4] = {0, 0, -1, 1};
	const static int dj[4] = {-1, 1, 0, 0};

	int N, M;
	scanf("%d %d", &N, &M);
	
	vector<string> grid(N);
	for (int i = 0; i < N; ++i) {
		cin >> grid[i];
	}

	deque<tuple<int, int, int>> Q{{0, 0, 1}};
	while (!Q.empty()) {
		auto coord = Q.front(); Q.pop_front();
		int i = get<0>(coord);
		int j = get<1>(coord);
		int depth = get<2>(coord);
		if (i == N-1 && j == M-1) {
			printf("%d\n", depth);
			break;
		}
		if (grid[i][j] != '1') {
			continue;
		}
		grid[i][j] = '*';
		for (int k = 0; k < 4; ++k) {
			int ii = i + di[k];
			int jj = j + dj[k];
			if (boundCheck2d(ii, jj, N, M) && grid[ii][jj] == '1') {
				Q.push_back({ii, jj, depth+1});
			}
		}
		
	}
	return 0;
}
