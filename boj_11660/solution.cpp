#include <bits/stdc++.h> 
using namespace std;

using LL = long long;

int main()
{
	int N, M;
	scanf("%d %d", &N, &M);
	
	vector<vector<LL>> grid(N, vector<LL>(N));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			scanf("%lld", &grid[i][j]);
		}
	}

	vector<vector<LL>> sums(N+1, vector<LL>(N+1, 0));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			sums[i+1][j+1] = sums[i][j+1] + sums[i+1][j] - sums[i][j] + grid[i][j];
		}
	}

	for (int i = 0; i < M; ++i) {
		int r1, c1;
		scanf("%d %d", &r1, &c1);
		int r2, c2;
		scanf("%d %d", &r2, &c2);
		
		LL ans = sums[r2][c2] - sums[r1-1][c2] - sums[r2][c1-1] + sums[r1-1][c1-1];
		printf("%lld\n", ans);
	}
	return 0;
}
