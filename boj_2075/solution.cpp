#include <bits/stdc++.h> 
using namespace std;


int main()
{
	int N;
	scanf("%d", &N);
	vector<vector<int>> grid(N, vector<int>(N, 0));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			scanf("%d", &grid[i][j]);
		}
	}

	priority_queue<tuple<int, int, int>> pq;
	for (int i = 0; i < N; ++i) {
		pq.push({grid[N-1][i], N-1, i});
	}
	for (int i = 0; i < N-1; ++i) {
		auto top = pq.top();
		pq.pop();
		if (get<1>(top) > 0) {
			pq.push({grid[get<1>(top)-1][get<2>(top)], get<1>(top)-1, get<2>(top)});
		}
	}
	printf("%d\n", get<0>(pq.top()));
	
	return 0;
}
