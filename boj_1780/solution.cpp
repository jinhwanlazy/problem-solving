#include <bits/stdc++.h> 
using namespace std;

struct Result 
{
	int a=0, b=0, c=0;
	
	Result& operator+=(const Result& rhs) {
		a += rhs.a;
		b += rhs.b;
		c += rhs.c;
		return *this;
	}

	friend ostream& operator<<(ostream& os, const Result& rhs) {
		os << rhs.a << "\n"
		   << rhs.b << "\n"
		   << rhs.c;
		return os;
	}
};

Result solution(const vector<vector<int>>& grid, int r, int c, int n)
{
	bool all_same = true;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (grid[r+i][c+j] != grid[r][c]) {
				all_same = false;
				break;
			}
		}
		if (!all_same) break;
	}
	if (all_same) {
		return Result{grid[r][c] == -1, grid[r][c] == 0, grid[r][c] == 1};
	}
	
	int cut = n / 3;
	Result res;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			res += solution(grid, r+cut*i, c+cut*j, cut);
		}
	}
	return res;
}

int main()
{
	int N;
	cin >> N;

	vector<vector<int>> grid(N, vector<int>(N));
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			scanf("%d", &grid[i][j]);
		}
	}

	cout << solution(grid, 0, 0, N) << "\n";

	return 0;
}
