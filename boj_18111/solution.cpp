#include <bits/stdc++.h> 
using namespace std;

int possible(const vector<vector<int>>& grid, int base_height, int B) 
{
	int required = 0;
	for (const auto& row : grid) {
		for(int h : row) {
			required += base_height - h;
		}
	}
	return required <= B;
}

int count_time(const vector<vector<int>>& grid, int base_height) {
	int count = 0;
	for (const auto& row : grid) {
		for(int h : row) {
			if (base_height > h) {
				count += base_height - h;
			}
			else {
				count += 2 * (h - base_height);
			}
		}
	}
	return count;
}

int main()
{
	int N, M, B;
	cin >> N >> M >> B;

	vector<vector<int>> grid(N, vector<int>(M));

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			scanf("%d", &grid[i][j]);
		}
	}

	int min_time = numeric_limits<int>::max();
	int best_height = 0;
	for (int h = 256; h >= 0; --h) {
		if (!possible(grid, h, B)) {
			continue;
		}
		int t = count_time(grid, h);
		if (t < min_time) {
			min_time = t;
			best_height = h;
		}
	}
	cout << min_time << " " << best_height << "\n";
	return 0;
}
